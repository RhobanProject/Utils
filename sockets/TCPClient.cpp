/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
#include <fcntl.h>
#include <iostream>
#include <string>

#include "TCPClient.h"

#ifndef WIN32
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <string.h>
#endif

using namespace std;

namespace Rhoban 
{
    TCPClient::TCPClient()
    {
        clientSocket = 0;
        connected = false;
    }

    TCPClient::~TCPClient()
    {
        stop();
    }

    void TCPClient::connectTo(const char *address, int port)
    {
#ifdef WIN32
		WSADATA wsa;
		WSAStartup(MAKEWORD(2,0), &wsa);
#endif

        stop();

        SOCKADDR_IN sin;
        memset(&sin, 0, sizeof(sin));
        struct hostent *hostinfo;
#ifdef LINUX
        clientSocket = socket(AF_INET, SOCK_STREAM|SOCK_CLOEXEC, 0);
#else
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);
#endif
        if (clientSocket == INVALID_SOCKET)
        {   
            connected = false;
            throw string("Could not create socket");
        }   

        hostinfo = gethostbyname(address);

        if (hostinfo == NULL)
        {   
            connected = false;
            throw string("Unknown host " + string(address));
        }   

        sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr;
        sin.sin_port = htons(port);
        sin.sin_family = AF_INET;

        if(connect(clientSocket, (SOCKADDR *)&sin, sizeof(SOCKADDR)) == SOCKET_ERROR) {
            connected = false;
            throw  string("Could not connect TCP client to ") + string(address);
        } 
#ifndef WIN32 
        int noDelay = 1;
        setsockopt(clientSocket, IPPROTO_TCP, TCP_NODELAY, (void *)&noDelay, sizeof(noDelay));
#endif

        connected = true;
    }
}
