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
#include <unistd.h>
#include <iostream>

#include "TCPServerClient.h"

using namespace std;

namespace Rhoban
{
    TCPServerClient::TCPServerClient()
    {
        dead = false;
    }

    TCPServerClient::~TCPServerClient()
    {
        pthread_cancel(thread);
        pthread_join(thread, NULL);
    }

    bool TCPServerClient::isDead()
    {
        return dead;
    }

    void TCPServerClient::stop()
    {
        close(clientSocket);
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
