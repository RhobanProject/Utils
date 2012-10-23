#ifndef _SUBJECT_H
#define _SUBJECT_H

#include <map>
#include <list>

#include "Observer.h"

using namespace std;

class Subject
{
    public:
        void registerObserver(string event, Observer *observer);
        void notifyObservers(string event);

    protected:
        map<string, list<Observer *> > observers;
};

#endif // _SUBJECT_H
