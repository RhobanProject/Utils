#include "Graph.h"

using namespace std;

Graph::Graph()
{
    gettimeofday(&startTime, NULL);
}

Curve *Graph::addCurve(string name)
{
    Curve *curve = new Curve(name, &startTime);
    curves.push_back(curve);

    return curve;
}
