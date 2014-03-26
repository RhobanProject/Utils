#include "Graph.h"

using namespace std;

Graph::Graph()
{
#ifndef WIN32
    gettimeofday(&startTime, NULL);
#else
	Rhoban::gettimeofday(&startTime, NULL);
#endif
}

Curve *Graph::addCurve(string name)
{
    Curve *curve = new Curve(name, &startTime);
    curves.push_back(curve);

    return curve;
}
