#ifndef _OBSERVER_H
#define _OBSERVER_H

#include <string>

using namespace std;

class Observer
{
    public:
        virtual void notify(string event)=0;
};

#endif // _OBSERVER_H
