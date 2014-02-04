#ifndef _ZMQ_CLIENT_H
#define _ZMQ_CLIENT_H

#include <string>

using namespace std;

class ZMQClient
{
    public:
        ZMQClient(string remote);
        virtual ~ZMQClient();

        void connect();
        string process(const string &request);

    protected:
        string remote;
        void *context;
        void *client;
};

#endif
