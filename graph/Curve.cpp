#include <iostream>
#include <sys/time.h>
#include "Curve.h"
#include "ticks.h"

using namespace std;

Curve::Curve(string name_, struct timeval *start_) : count(0), start(start_), name(name_)
{
    values = new deque<CurveEntry*>();
}

Curve::~Curve()
{
    delete values;
}

void Curve::push(double value)
{
    CurveEntry *entry = new CurveEntry(value, elapsed());
    values->push_back(entry);
}

double Curve::elapsed()
{
    struct timeval n;
    gettimeofday(&n, NULL);
    decrease(n, *start);

    return to_secs(n);
}
        
vector<pair<double, double> > Curve::getValues(double time)
{
    vector<pair<double, double> > vals;
    double nowTime = elapsed();

    count++;
    if (count%CURVE_GC) {
        garbageCollect(CURVE_EXPIRATION);
    }

    for (deque<CurveEntry*>::reverse_iterator it = values->rbegin(); it != values->rend(); it++) {
        CurveEntry *entry = (*it);

        if (nowTime-entry->time > time) {
            break;
        } else {
            pair<double, double> p(entry->time, entry->value);
            vals.push_back(p);
        }
    }

    return vals;
}
        
void Curve::garbageCollect(double expiration)
{
    int toDelete = 0;
    double nowTime = elapsed();

    for (deque<CurveEntry*>::iterator it = values->begin(); it != values->end(); it++) {
        CurveEntry *entry = (*it);

        if (nowTime - entry->time < expiration) {
            if (it != values->begin()) {
                values->erase(values->begin(), it);
            }
            break;
        }
    }
}
