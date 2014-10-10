#ifndef ZMQ_CONTEXT_H
#define ZMQ_CONTEXT_H

namespace Rhoban
{
	/* ZMQ recommends one context only per process, this function provides a singleton context */
	extern void * get_zmq_context();
}

#endif