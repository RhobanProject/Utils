#include <string>
#include <iostream>
#include "ZMQClient.h"
#include "zhelpers.h"

using std::string;

ZMQClient::ZMQClient(string remote_)
    : context(NULL), client(NULL)
{
    remote = remote_;
    context = zmq_ctx_new();
    client = zmq_socket(context, ZMQ_REQ);
    connect();
}

void ZMQClient::connect()
{
    if (zmq_connect(client, remote.c_str()) != 0) {
        throw std::runtime_error("Unable to connect");
    }

    int timeout = 1000;
    zmq_setsockopt(client, ZMQ_RCVTIMEO, &timeout, sizeof(timeout));
    timeout = 100;
    zmq_setsockopt(client, ZMQ_LINGER, &timeout, sizeof(timeout));
}

void ZMQClient::setTimeout(double timeout_)
{
    int timeout = timeout_*1000;
    zmq_setsockopt(client, ZMQ_RCVTIMEO, &timeout, sizeof(timeout));
    timeout = timeout_*1000;
    zmq_setsockopt(client, ZMQ_LINGER, &timeout, sizeof(timeout));
}

ZMQClient::~ZMQClient()
{
    if (client != NULL) {
        zmq_close(client);
    }
    if (context != NULL) {
        zmq_ctx_destroy(context);
    }
}

string ZMQClient::process(const string &request)
{
    s_send(client, request.c_str());
    char *response = s_recv(client);

    if (response == NULL) {
        throw std::runtime_error("Unable to talk with the server");
    }

    string resp(response);
    free(response);

    return resp;
}
