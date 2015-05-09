#ifndef _ZMQ_SERVER_H
#define _ZMQ_SERVER_H

#include <sstream>
#include <iostream>
#include <string>
#include <threading/Thread.h>
#include "zhelpers.h"
#include <zmq/ZMQContext.h>

template<typename T>
class ZMQServer : public Rhoban::Thread
{
public:
	ZMQServer(int port, T &processor_, bool create_context = true)
		: context(NULL), server(NULL), processor(processor_), create_context(create_context)
	{
		if (new_context)
			context = zmq_ctx_new();
		else
			context = Rhoban::get_zmq_context();

		server = zmq_socket(context, ZMQ_REP);

		std::string addr = "tcp://*:" + to_string(port);

		if (zmq_bind(server, addr.c_str()) != 0)
			throw runtime_error("Unable to bind server");
	}

	virtual ~ZMQServer()
	{
		if (server != NULL)
			zmq_close(server);

		if (create_context && (context != NULL))
			zmq_ctx_destroy(context);

		server = NULL;
		context = NULL;
	}

	void run()
	{
		zmq_msg_t message;
		zmq_msg_init(&message);

		while (processor.isRunning()) {
			int size = zmq_msg_recv(&message, server, 0);
			if (size != -1)
			{
				std::string response = processor.process(std::string((char *)zmq_msg_data(&message), size));
				zmq_msg_init_size(&message, response.size());
				memcpy(zmq_msg_data(&message), response.c_str(), response.size());
				zmq_msg_send(&message, server, 0);
			}
		}
	}

	void execute()
	{
		run();
	}

protected:
	void *context;
	void *server;
	T &processor;
	bool create_context;
};

#endif
