#include "Poller.h"

void Poller::startPolling(int frequency)
{
    init(frequency);
}

void Poller::add(Pollable *pollable)
{
    lock.lock();
    objects.push_back(pollable);
    lock.unlock();
}

void Poller::step()
{
    lock.lock();
    for (vector<Pollable*>::iterator it=objects.begin(); it!=objects.end(); it++) {
        (*it)->poll();
    }
    lock.unlock();
}
