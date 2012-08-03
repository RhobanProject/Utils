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

#include "TCPServerClient.h"

using namespace std;

namespace Rhoban
{
    TCPServerClient::TCPServerClient(int socket)
    {
        clientSocket = socket;
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

    void TCPServerClient::run()
    {
        pthread_create(&thread, NULL, TCPServerClient::clientThread, (void*)this);
    }

    void *TCPServerClient::clientThread(void *clientPtr)
    {
        TCPServerClient *client = (TCPServerClient *)clientPtr;

        try {
            client->loop();
        } catch (string exception) {
            cout << "Closing client (" << exception << ")" << endl;
        }

        client->stop();

        return NULL;
    }
}
