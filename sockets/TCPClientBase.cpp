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
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdarg.h>
#include <string.h>
#include <string>
#include <sstream>

#include <sockets/TCPClientBase.h>

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
		if (n < 0 && errno != EAGAIN && errno != WSAEWOULDBLOCK ) {
#else 
        if (n < 0 && errno != EAGAIN && errno != EWOULDBLOCK) {
#endif
            throw string("Error while receiving data");
        }

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
        vsscanf(str.c_str(), format, args);
        va_end(args);
    }

    int TCPClientBase::transmit(const char *buffer, int size)
    {
        int n = send(clientSocket, buffer, size, 0);

#ifdef WIN32
	if (n < 0 && errno != EAGAIN && errno != WSAEWOULDBLOCK ) {
#else 
        if (n < 0 && errno != EAGAIN && errno != EWOULDBLOCK) {
#endif
            throw string("Error while sending data");
        }

        return n;
    }

    void TCPClientBase::transmitString(string str, bool lineTerminates)
    {
        char buffer[str.length()+1];

        memcpy(buffer, str.c_str(), sizeof(buffer));

        if (lineTerminates) {
            buffer[sizeof(buffer)-1] = '\n';
        }

        transmit(buffer, sizeof(buffer));
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
        if (clientSocket) {
            close(clientSocket);
        }
    }
}
