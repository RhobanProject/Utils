
#include "ZMQContext.h"
#include <threading/Thread.h>

#ifdef WIN32
#include <zmq/include/zmq.h>
#else
#ifdef MACOSX
#include <zmq/include/zmq.h>
#else
#include <zmq.h>
#endif
#endif

using namespace std;

void * context = NULL;
Rhoban::Mutex zmq_context_mutex;

	/* ZMQ recommends one context per process */
void * Rhoban::get_zmq_context()
{
	BEGIN_SAFE(zmq_context_mutex)
if(context == NULL)
	context = zmq_ctx_new();
	END_SAFE(zmq_context_mutex)
return context;
}

void Rhoban::destroy_zmq_context()
{
	BEGIN_SAFE(zmq_context_mutex)
		if (context != NULL)
			zmq_ctx_destroy(&context);
		context = NULL;
	END_SAFE(zmq_context_mutex)

}

