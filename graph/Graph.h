#ifndef _GRAPH_H
#define _GRAPH_H

#include <vector>
#include "ticks.h"
#include "Curve.h"

using namespace std;

class Graph
{
    public:
        Graph();
        Curve *addCurve(string name);

    protected:
        vector<Curve*> curves;
        struct timeval start;
};

#endif // _GRAPH_H
