/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
#include <cstdlib>
#include <iostream>

#include <sockets/TCPServer.h>
#include <sockets/TCPClient.h>

#include <sockets/demo/DemoServerClient.h>
#include <main/Command.h>

using namespace std;
using namespace Rhoban;

COMMAND_DEFINE(demo_server, "Socket demo server")
{
    TCPServer<DemoServerClient> *server = new TCPServer<DemoServerClient>;

    cout << "*** Creating \"echo\" DemoServer" << endl;
    server->run(1234);
}

COMMAND_DEFINE(demo_client, "Socket demo client")
{
    int a,b;
    TCPClient *client = new TCPClient;

    a = 12;
    b = 34;

    client->connectTo("localhost", 1234);
    client->transmitFormat("a=%d, b=%d\n", a, b);
    client->receiveFormat("a=%d, b=%d", &a, &b);
    cout << "Values (a=" << a << ", b=" << b << ")" << endl;
    client->stop();
}
