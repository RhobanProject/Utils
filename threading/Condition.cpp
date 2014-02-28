/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ctime>

#include <timing/chrono.h>

#ifndef MSVC
#include <pthread.h>
#endif

#include <cerrno>
#include <iostream>

#include "Condition.h"

using namespace std;
using namespace Rhoban;

Condition::Condition()
{
#ifndef MSVC
	int ret = pthread_cond_init(&condition, 0 );
    if(ret==-1) {
        throw string("Failed to init condition");
    }
#else
	InitializeConditionVariable(&condition);
#endif
#ifdef DEBUG_MUTEXES
	cout << "Thread " <<  (int) pthread_self().p << " initialized condition " << (int) this << endl;
#endif

}

Condition::~Condition()
{
#ifndef MSVC
	pthread_cond_destroy(&condition);
#endif
}

int Condition::wait(Mutex * mutex, unsigned int timeout)
{
    int ret;
#ifndef MSVC
    struct timespec time;
    chrono tv;

    gettimeofday(&tv, NULL);

    time.tv_sec = tv.tv_sec + (timeout/1000);
    time.tv_nsec = (tv.tv_usec*1000) + ((timeout%1000) * 1000000);

    if (time.tv_nsec >= 1000000000L) {
        time.tv_sec++;
        time.tv_nsec -= 1000000000L;
    }

    if (timeout > 0) {
        ret = pthread_cond_timedwait(&condition, &(mutex->_mutex), &time);
    } else {
        ret = pthread_cond_wait(&condition, &(mutex->_mutex));
    }

    if (ret == ETIMEDOUT) {
        throw string("Timeout while waiting for condition");
    }
#else
	ret = sys_wait_msConditionVariableCS(&condition,&(mutex->_mutex),timeout) ? 0 : -1;
	if (ret < 0)
	{
		cout << "Failed to wait condition with error " << GetLastError() << endl;
	}
#endif
    if (ret < 0) {
        throw string("Failed to wait condition");
    }

    return 1;
}

int Condition::wait(unsigned int timeout)
{
#ifdef DEBUG_MUTEXES
	cout << "Thread " <<  (int) pthread_self().p << " waiting condition " << (int) this << endl;
#endif
	return wait(this, timeout);
#ifdef DEBUG_MUTEXES
	cout << "Thread " <<  (int) pthread_self().p << " waited condition " << (int) this << endl;
#endif
}

void Condition::broadcast()
{
#ifdef DEBUG_MUTEXES
	cout << "Thread " <<  (int) pthread_self().p << " broadcasting condition " << (int) this << endl;
#endif
#ifndef MSVC
    int ret = pthread_cond_broadcast(&condition);
    if(ret==-1)
        throw string("Failed to broadcast condition");
#else
	WakeConditionVariable(&condition);
#endif
#ifdef DEBUG_MUTEXES
	cout << "Thread " <<  (int) pthread_self().p << " broadcasted condition " << (int) this << endl;
#endif
}

