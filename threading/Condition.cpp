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
#include <pthread.h>
#include <cerrno>
#include <sys/time.h>

#include "Condition.h"

using namespace std;

Condition::Condition()
{
    int ret = pthread_cond_init(&condition, 0 );

    if(ret==-1) {
        throw string("Failed to init condition");
    }
}

Condition::~Condition()
{
		pthread_cond_destroy(&condition);
}

int Condition::wait(Mutex * mutex, unsigned int timeout)
{
    int ret;
    struct timespec time;
    struct timeval tv;

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

    if (ret < 0) {
        throw string("Failed to wait condition");
    }

    return 1;
}

int Condition::wait(unsigned int timeout)
{
	wait(this, timeout);
}

void Condition::broadcast()
{
    int ret = pthread_cond_broadcast(&condition);

    if(ret==-1) {
        throw string("Failed to broadcast condition");
    }
}

