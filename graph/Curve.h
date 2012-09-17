#ifndef _CURVE_H
#define _CURVE_H

#include <deque>
#include <vector>
#include <string>
#include <time.h>
#include <sys/time.h>

#include "CurveEntry.h"

using namespace std;

#define CURVE_EXPIRATION 5.0
#define CURVE_GC 1000

class Curve
{
    public:
        Curve(string name_, struct timeval *start_);
        ~Curve();
        void push(double value);
        vector<pair<double, double> > getValues(double time);
        void garbageCollect(double expiration);
        double elapsed();

        string name;

    protected:
        struct timeval *start;
        deque<CurveEntry*> *values;
        int count;
};

#endif // _CURVE_H
