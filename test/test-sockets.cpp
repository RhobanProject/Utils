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
#include <string>

#include <timing/sleep.h>
#include <logging/log.h>

#include <tests/TestCase.h>
#include <tests/runTests.h>

#include <sockets/TCPClient.h>
#include <sockets/TCPServer.h>
#include <sockets/TCPServerClient.h>

using namespace std;
using namespace Rhoban;

#define TEST_LOG(...) LOG(1, 1, "test", __VA_ARGS__)

class EchoClient : public TCPServerClient
{
    public:
        EchoClient(int socket) : TCPServerClient(socket)
        {
        }

        void loop()
        {
            int size;
            char buffer[128];

            TEST_LOG("Client connected, entering receive loop");
            while (1) {
                size = receive(buffer, sizeof(buffer));
                transmit(buffer, size);
            }
        }
};

void *run_server(void *data)
{
    try {
        TCPServer<EchoClient> server;
        server.run(9696);
    } catch (string error) {
        TEST_LOG("Server error: %s", error.c_str())
    }
};

class TestSockets : public TestCase
{
    public:
        void testClientServer()
        {
            pthread_t serverThread;
            char buffer[128];
            char testString[] = "Hello";
            TCPClient client;

            TEST_LOG("Running server...");
            pthread_create(&serverThread, NULL, run_server, NULL);
            ms_sleep(1000);

            TEST_LOG("Connecting client...");
            client.connectTo("localhost", 9696);

            assertTrue(client.isConnected());

            TEST_LOG("Transmitting echo...");
            client.transmit(testString, strlen(testString));

            TEST_LOG("Receiving...");
            client.receiveAll(buffer, strlen(testString));
            buffer[strlen(testString)] = '\0';

            assertEquals(strcmp(testString, buffer), 0);

            TEST_LOG("End");
            client.stop();
        }

    protected:
        void _run()
        {
            testClientServer();
        }
};

int main(void)
{
    try {
        runTests<TestSockets>("Sockets testing");
    } catch (string error) {
        TEST_LOG("Error: %s", error.c_str())
    }
}
