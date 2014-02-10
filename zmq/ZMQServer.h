#ifndef _ZMQ_SERVER_H
#define _ZMQ_SERVER_H

#include <sstream>
#include <iostream>
#include <string>
#include "zhelpers.h"

template<typename T>
class ZMQServer
{
    public:
        ZMQServer(int port, T &processor_)
            : context(NULL), server(NULL), processor(processor_)
        {
            context = zmq_ctx_new();
            server = zmq_socket(context, ZMQ_REP);

            std::ostringstream oss;
            oss << "tcp://*:" << port;
            std::string addr = oss.str();
            
            if (zmq_bind(server, addr.c_str()) != 0) {
                throw std::string("Unable to bind server");
            }
        }

        virtual ~ZMQServer()
        {
            if (server != NULL) {
                zmq_close(server);
            }
            if (context != NULL) {
                zmq_ctx_destroy(context);
            }
        }

        void run()
        {
            while (processor.isRunning()) {
                char *request = s_recv(server);
                std::string response = processor.process(std::string(request));
                s_send(server, response.c_str());
                free(request);
            }
        }

    protected:
        T &processor;
        void *context;
        void *server;
};

#endif
