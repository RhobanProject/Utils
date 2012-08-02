/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
#include <iostream>

#include <sockets/demo/DemoServerClient.h>

using namespace std;

namespace Rhoban
{
    DemoServerClient::DemoServerClient(int socket) : TCPServerClient(socket)
    {
    }

    void DemoServerClient::loop()
    {
        int n;
        char buffer[128];

        cout << "Entering the loop" << endl;

        n = receive(buffer, sizeof(buffer));
        transmit(buffer, n);
        stop();
    }
}
