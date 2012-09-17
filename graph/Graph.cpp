#include "Graph.h"

using namespace std;

Graph::Graph()
{
    gettimeofday(&start, NULL);
}

Curve *Graph::addCurve(string name)
{
    Curve *curve = new Curve(name, &start);
    curves.push_back(curve);

    return curve;
}
