/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
#ifndef _TCPSERVER_H
#define _TCPSERVER_H

#ifdef WIN32
#include <io.h>
#endif

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <string>

#include <vector>
#include "common.h"
#include "TCPServerClient.h"

using namespace std;

namespace Rhoban
{
    template<class T>
        class TCPServer
        {
            public:
                TCPServer()
                {
#ifndef WIN32
                    signal(SIGPIPE, SIG_IGN);
#endif
                }

                ~TCPServer()
                {
                    shutdown();

                    deleteAllClients();

#ifdef WIN32
                    WSACleanup();
#endif
                }

                /**
                 * Deleting the server clients
                 */
                void deleteAllClients()
                {
                    while (clients.size() > 0) {
                       T *client = clients.back();
                        cleanClient(client);

                        clients.pop_back();
                    }
                }

                /**
                 * Starts listening on the given port
                 *
                 * This will be blocking and will call
                 */
                virtual void run(int port, bool localhostOnly = false)
                {
#ifdef WIN32
                    WSADATA wsa;
                    WSAStartup(MAKEWORD(2,0), &wsa);
#else
                    signal(SIGPIPE, SIG_IGN);
#endif

                    // Initializing the sinserv
                    memset(&sinserv, 0, sizeof(sinserv));
                    sinserv.sin_family = AF_INET;
                    sinserv.sin_addr.s_addr = localhostOnly ? inet_addr("127.0.0.1") : INADDR_ANY;
                    sinserv.sin_port = htons(port);

                    socketDescriptor = socket(AF_INET, SOCK_STREAM|SOCK_CLOEXEC, 0); 

                    if (socketDescriptor == INVALID_SOCKET)
                    {  
                        perror("socket()");
                        throw string("Failed to create socket");
                    } 

#ifdef _WIN32
                    char on = 1;
#else
                    int on = 1;
#endif
                    if (setsockopt(socketDescriptor, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0) {
                        throw string("Failed to set socket options");
                    }

                    if (bind(socketDescriptor, (SOCKADDR*) &sinserv, sizeof(sinserv)))
                    {
                        perror("bind()");
                        throw string("Failed to bind socket");
                    }

                    if (listen(socketDescriptor, 32) == SOCKET_ERROR)
                    {
                        perror("listen()");
                        throw string("Failed to listen incoming connections");
                    }

                    acceptLoop();
                }

                /**
                 * Shutdowns the server
                 */
                virtual void shutdown()
                {
                    if (socketDescriptor) {
                        close(socketDescriptor);
                    }

                    socketDescriptor = 0;
                }

                /**
                 * Cleans a client (default behaviour is removing it)
                 */
                virtual void cleanClient(T * client)
                {
                    delete client;
                }

                /**
                 * Deletes a client
                 */
                virtual void deleteClient(T *client)
                {
                    for (typename vector<T *>::iterator i = clients.begin(); i != clients.end(); i++) {
                        T *current = *i;

                        if (current == client) {
                            client->stop();
                            clients.erase(i);
                            cleanClient(client);

                            break;
                        }
                    }
                }

                /**
                 * Delete clients
                 */
                void deleteClients(vector<T *> &clients)
                {
                    for (typename vector<T *>::iterator i = clients.begin(); i != clients.end(); i++) {
                        deleteClient(*i);
                    }
                }

            protected:
                /**
                 * Socket file descriptor
                 */
                SOCKET socketDescriptor;

                /**
                 * Server in address
                 */
                struct sockaddr_in sinserv;

                /**
                 * Clients
                 */
                vector<T *> clients;

                /**
                 * Creating a client, can be overloaded
                 */
                virtual T *createClient()
                {
                    return new T();
                }

                /**
                 * Accepting connection loop
                 */
                void acceptLoop()
                {
                    int addrSize;
                    volatile SOCKET newClient;
                    struct sockaddr_in clientAddr;
                    vector<T *> dead;

                    while (socketDescriptor) {
                        addrSize = sizeof(clientAddr);

                        // Waiting for a connection
#ifdef _WIN32
                        newClient = accept(socketDescriptor, (SOCKADDR*)&clientAddr, &addrSize);
#else
                        newClient = accept(socketDescriptor, (SOCKADDR*)&clientAddr, (socklen_t*) &addrSize);
#endif

                        if (newClient != INVALID_SOCKET) {
                            T *client = createClient();
                            client->setSocket(newClient);
                            clients.push_back(client);
                            client->start(NULL);
                        } else {
                            socketDescriptor = 0;
                        }

                        // Deleting dead clients
                        for (typename vector<T *>::iterator i = clients.begin(); i != clients.end(); i++) {
                            T *client = *i;

                            if (client->isDead()) {
                                dead.push_back(client);
                            }
                        }

                        deleteClients(dead);
                        dead.clear();
                    }

                    // Deleting all the clients
                    deleteAllClients();
                }
        };
}

#endif // _TCPSERVER_H
