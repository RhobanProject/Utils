#ifndef _ZMQ_READER_H
#define _ZMQ_READER_H

#include <sstream>
#include <iostream>
#include <string>
#include <threading/Thread.h>
#include "zhelpers.h"
#include <zmq/ZMQContext.h>

template<typename T>
class ZMQReader : public Rhoban::Thread
{
public:
 ZMQReader(string ip, int port, T &processor_, string filter = "")
		: reader(NULL), processor(processor_)
	{
		reader = zmq_socket( Rhoban::get_zmq_context(), ZMQ_SUB);

		std::string addr = "tcp://" + ip + ":" + to_string(port);

		int timeout = 1000;
		zmq_setsockopt(reader, ZMQ_RCVTIMEO, &timeout, sizeof(timeout));
		timeout = 100;
		zmq_setsockopt(reader, ZMQ_LINGER, &timeout, sizeof(timeout));
		zmq_setsockopt(reader, ZMQ_SUBSCRIBE, filter.c_str(), filter.size());

		if (zmq_connect(reader, addr.c_str()) != 0)
			throw runtime_error("Unable to connect reader to publisher '"+ addr + "'");

}

	virtual ~ZMQReader()
	{
		Thread::kill();
		if (reader != NULL)
			zmq_close(reader);
		reader = NULL;
	}

	void execute()
	{
		zmq_msg_t message;
		zmq_msg_init(&message);

		while (Thread::is_alive()) {
			int size = zmq_msg_recv(&message, reader, 0);
			if (size > 0)
				processor.read(std::string((char *)zmq_msg_data(&message), size));
		}
		cout << "reader dying" << endl;
	}

protected:
	void *reader;
	T &processor;
};

#endif
