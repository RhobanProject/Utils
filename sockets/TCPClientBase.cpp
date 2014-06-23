/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
#include <stdlib.h>
#include <stdio.h>
#ifndef WIN32
#include <fcntl.h>
#endif
#include <iostream>
#ifndef MSVC
#include <unistd.h>
#endif
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdarg.h>
#include <string.h>
#include <string>
#include <sstream>
#include "util.h"

#include "TCPClientBase.h"

#include <timing/chrono.h>

#define FD_ZERO2(p)     memset((p), 0, sizeof(*(p)))

using namespace std;

namespace Rhoban
{
    int TCPClientBase::receive(char *buffer, int size)
    {
        int n = recv(clientSocket, buffer, size, 0);

        if (n == 0) {
            throw string("Connection closed");
        }

#ifdef WIN32
	
		if (n < 0)
		{
			int err = WSAGetLastError();
			if (err != EAGAIN && err != WSAEWOULDBLOCK) {
				connected = false;
				stringstream ss;
				ss << "Error while receiving data from client socket " << clientSocket;
				throw std::runtime_error(ss.str());
			}

		}

#else 
        if (n < 0 && errno != EAGAIN && errno != EWOULDBLOCK) {
			connected = false;
			ostringstream err;
			err << "Error while receiving data from client socket " << clientSocket;
			err << " (" << strerror(errno) << ")";
			throw err.str();
		}
#endif

        return n;
    }

    void TCPClientBase::receiveAll(char *buffer, int size)
    {
        int n;

        while (size > 0) {
            n = receive(buffer, size);
            buffer += n;
            size -= n;
        }
    }
            
    bool TCPClientBase::waitReady(int timeout_ms)
    {
        fd_set rdfs;
        struct timeval tv;
        int res = 0;

        FD_ZERO2(&rdfs);
        FD_SET(clientSocket, &rdfs);

        if (timeout_ms) {
            tv.tv_sec = timeout_ms / 1000;
            tv.tv_usec = 1000 * (timeout_ms % 1000);
            res = select(clientSocket + 1, &rdfs, NULL, NULL, &tv);
        } else {
            res = select(clientSocket + 1, &rdfs, NULL, NULL, NULL);
        }

        if (res == 0) {
            return false;
        } else if( res == -1) {
            stop();
#ifdef _WIN32
            int err = WSAGetLastError();
            throw string("Client : select error (WSA error code)");
#else
            throw string ("Client : select error");
#endif
        }

        return true;
    }

    string TCPClientBase::receiveStringMaxSize(int size)
    {
#ifndef MSVC
        char c[size];
        int n = receive(c, size);
        return string(c, n);
#else
		char * c = (char *)malloc(size);
		int n = receive(c, size);
		string answer(c, n);
		delete c;
		return answer;
#endif

    }
            
    string TCPClientBase::receiveStringSize(int size)
    {
        int n, total = 0;
        char c;
        ostringstream stream;

        while (true) {
            n = receive(&c, 1);

            if (n == 1) {
                stream << c;
                total++;
                if (total >= size) {
                    break;
                }
            } else {
                break;
            }
        }

        return stream.str();
    }

    string TCPClientBase::receiveString(bool lineTerminates)
    {
        int n;
        char c;
        ostringstream stream;

        while (true) {
            n = receive(&c, 1);

            if (n == 1) {
                if (c == '\0' || (lineTerminates && c == '\n')) {
                    break;
                }

                stream << c;
            }
        }

        return stream.str();
    }

    void TCPClientBase::receiveFormat(const char *format, ...)
    {
        va_list args;
        string str = receiveString(true);

        va_start(args, format);
#ifdef MSVC
		throw string("TCPClientBase::receiveFormat unimplemented");
#else
		vsscanf(str.c_str(), format, args);
#endif
        va_end(args);
    }

    int TCPClientBase::transmit(const char *buffer, int size)
    {
		if (size == 0)
			return 0;

        int n = send(clientSocket, buffer, size, 0);


#ifdef WIN32
		if (n <= 0)
		{
			int err = WSAGetLastError();
			if (err != EAGAIN && err != WSAEWOULDBLOCK) {
				connected = false;
				stringstream ss;
				ss << "Error while sending data to client socket " << clientSocket;
				throw std::runtime_error(ss.str());
			}
		}
#else 
        if (n < 0 && errno != EAGAIN && errno != EWOULDBLOCK) {
            connected = false;
			throw std::runtime_error("Error while sending data");
        }
#endif

        return n;
    }
    
    void TCPClientBase::transmitAll(const char *buffer, int size)
    {
        int n;

        while (size > 0) {
            n = transmit(buffer, size);
            buffer += n;
            size -= n;
        }
    }

    void TCPClientBase::transmitString(string str, bool lineTerminates)
    {
        string buffer = str;

        if (lineTerminates) {
	    buffer.resize(str.size()+1);
            buffer[buffer.size()-1] = '\n';
        }

	transmitAll(buffer.c_str(), buffer.length());
    }

    void TCPClientBase::transmitFormat(const char *format, ...)
    {
        va_list args;
        int n, size = 100;
        char *p, *np;

        if ((p = (char*)malloc(size)) == NULL) {
            throw string("Error while transmitting message");
        }

        while (true ) {
            va_start(args, format);
            n = vsnprintf(p, size, format, args);
            va_end(args);

            if (n > -1 && n < size) {
                break;
            }

            if (n > -1) { 
                size = n+1;
            } else {
                size *= 2; 
            } if ((np = (char*)realloc(p, size)) == NULL) {
                free(p);
                throw string("Error while transmitting message");
            } else {
                p = np;
            }
        }

        transmitString(string(p));

        free(p);
    }

    void TCPClientBase::setBlocking(int blocking)
    {
#ifdef WIN32
        unsigned long arg;

        arg = blocking ? 1 : 0;

        ioctlsocket(clientSocket, FIONBIO, &arg); 
#else
        int flags;

        flags = fcntl(clientSocket, F_GETFL);

        if (blocking) {
            fcntl(clientSocket, F_SETFL, flags & ~O_NONBLOCK);   
        } else {
            fcntl(clientSocket, F_SETFL, flags | O_NONBLOCK); 
        }
#endif
    }

    void TCPClientBase::stop()
    {
		if (clientSocket && clientSocket != INVALID_SOCKET) {
#ifdef WIN32
            closesocket(clientSocket);
			Sleep(200);
#else
            close(clientSocket);
#endif
			clientSocket = INVALID_SOCKET;
		}

        connected = false;
    }

    bool TCPClientBase::isConnected()
    {
        return connected;
    }
}
