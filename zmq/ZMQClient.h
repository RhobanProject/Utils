#ifndef _ZMQ_CLIENT_H
#define _ZMQ_CLIENT_H

#include <string>

using namespace std;

class ZMQClient
{
    public:
        ZMQClient(string remote);
        virtual ~ZMQClient();

        string process(const string &request);

    protected:
        void *context;
        void *client;
};

#endif
