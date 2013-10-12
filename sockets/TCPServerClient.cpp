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
        } catch (string exception_) {
            cout << "Closing client (" << exception_ << ")" << endl;
        }

        stop();
    }

    void TCPServerClient::setSocket(SOCKET socket)
    {
        clientSocket = socket;
    }
}
