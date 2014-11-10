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

#ifndef MSVC
#include <unistd.h>
#endif

#include <iostream>

#ifndef WIN32
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#endif

#include "TCPServerClient.h"

using namespace std;

namespace Rhoban
{
    TCPServerClient::TCPServerClient()
    {
        dead = false;
#ifndef WIN32
        signal(SIGPIPE, SIG_IGN);
#endif
    }

    TCPServerClient::~TCPServerClient()
    {
    }

    bool TCPServerClient::isDead()
    {
        return dead;
    }

    void TCPServerClient::closeSocket()
    {
        if (clientSocket != INVALID_SOCKET) {
#ifdef MSVC
			closesocket(clientSocket);
#else
            close(clientSocket);
#endif
        }
        clientSocket = INVALID_SOCKET;
    }

    void TCPServerClient::stop()
    {
        closeSocket();
        dead = true;
    }

    void TCPServerClient::execute()
    {
        try {
            loop();
        } catch (const std::runtime_error & exception_) {
          cout << "Closing client (" << exception_.what() << ")" << endl;
        }

        stop();
    }

    void TCPServerClient::setSocket(SOCKET socket)
    {
        clientSocket = socket;

#ifndef WIN32
        int noDelay = 1;
        setsockopt(clientSocket, IPPROTO_TCP, TCP_NODELAY, (void *)&noDelay, sizeof(noDelay));
#endif
    }
}
