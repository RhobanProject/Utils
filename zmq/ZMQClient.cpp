#include <string>
#include <iostream>
#include "ZMQClient.h"
#include "zhelpers.h"

#include <stdexcept>

using namespace std;

ZMQClient::ZMQClient(string remote_)
    : context(NULL), client(NULL)
{
  remote = remote_;
    context = zmq_ctx_new();
    connect();
}

void ZMQClient::connect()
{
	if (client)
		zmq_close(client);

	client = zmq_socket(context, ZMQ_REQ);
	
	if (zmq_connect(client, remote.c_str()) != 0) {
        throw runtime_error("Unable to connect");
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
  zmq_msg_t message;
  zmq_msg_init(&message);

  zmq_msg_init_size(&message, request.size());
  memcpy(zmq_msg_data(&message), request.c_str(), request.size());
  zmq_msg_send(&message, client, 0);
  int size = zmq_msg_recv(&message, client, 0);
    if (size == -1) {
        throw runtime_error("Unable to get reponse from the server");
    }
    string response((char *)zmq_msg_data(&message), size);
    zmq_msg_close(&message);
    return response;
}
