#include "Subject.h"

void Subject::registerObserver(string event, Observer *observer)
{
    observers[event].push_back(observer);
}

void Subject::notifyObservers(string event)
{
    list<Observer *> *observerList = &observers[event];

    for (list<Observer *>::iterator it=observerList->begin(); it!=observerList->end(); it++) {
        Observer *observer = *it;
        observer->notify(event);
    }
}
