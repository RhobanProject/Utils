#ifndef _POLLER_H
#define _POLLER_H

#include "Pollable.h"
#include "Mutex.h"
#include "TimedThread.h"

class Poller : public TimedThread
{
    public:
        void startPolling(int frequency);
        void step();
        void add(Pollable *objects);

    protected:
        vector<Pollable *> objects;
        Mutex lock;
};

#endif // _POLLER_H
