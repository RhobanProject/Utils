#include <string>
#include <iostream>
#include "ZMQClient.h"
#include "zhelpers.h"

ZMQClient::ZMQClient(string remote)
    : context(NULL), client(NULL)
{
    context = zmq_ctx_new();
    client = zmq_socket(context, ZMQ_REQ);

    if (zmq_connect(client, remote.c_str()) != 0) {
        throw string("Unable to connect");
    }
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
        return "";
    }

    string resp(response);
    free(response);

    return resp;
}