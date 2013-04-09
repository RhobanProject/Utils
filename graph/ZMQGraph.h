#ifndef _ZMQ_GRAPH_H
#define _ZMQ_GRAPH_H

#include <threading/Thread.h>
#include "Graph.h"

class ZMQGraph : public Graph, public Rhoban::Thread
{
    public:
        ZMQGraph(string address);
        void execute();

    protected:
        void *socket;
};

#endif // _ZMQ_GRAPH_H
