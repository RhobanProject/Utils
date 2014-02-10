#ifndef _ZMQ_CLIENT_H
#define _ZMQ_CLIENT_H

#include <string>

class ZMQClient
{
    public:
        ZMQClient(std::string remote);
        virtual ~ZMQClient();

        void connect();
        std::string process(const std::string &request);

    protected:
        std::string remote;
        void *context;
        void *client;
};

#endif
