#ifndef _ZMQ_PUBLISHER_H
#define _ZMQ_PUBLISHER_H

#include <sstream>
#include <iostream>
#include <string>
#include <threading/Thread.h>
#include "zhelpers.h"
#include <zmq/ZMQContext.h>

class ZMQPublisher
{
public:
	ZMQPublisher(int port)
		: server(NULL)
	{
		server = zmq_socket( Rhoban::get_zmq_context() , ZMQ_PUB);
		std::string addr = "tcp://*:" + to_string(port);

		zmq_msg_init(&message);

		if (zmq_bind(server, addr.c_str()) != 0)
			throw runtime_error("Unable to bind publish server to '" + addr + "'");
		else
		  cout << "Created publisher on port " << port << endl;
	}

	virtual ~ZMQPublisher()
	{
		if (server != NULL)
			zmq_close(server);
		server = NULL;
	}

	void publish(string data)
	{
		zmq_msg_init_size(&message, data.size());
		memcpy(zmq_msg_data(&message), data.c_str(), data.size());
		zmq_msg_send(&message, server, 0);
	}

protected:
	void *server;
	zmq_msg_t message;
};

#endif
