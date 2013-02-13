/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
#include <pthread.h>
#include <string>
#include <iostream>

#include "Mutex.h"

using namespace std;

Mutex::Mutex(void)
{
#ifdef DEBUG_MUTEXES
	cout << "Thread " <<  (int) pthread_self().p << " initializing mutex " << (int) this << endl;
#endif
    pthread_mutex_init(&_mutex, NULL);
#ifdef DEBUG_MUTEXES
	cout << "Thread " <<  (int) pthread_self().p << " inittilized mutex " << (int) this << endl;
#endif
}

Mutex::~Mutex(void)
{
#ifdef DEBUG_MUTEXES
	cout << "Thread " <<  (int) pthread_self().p << " destroying mutex " << (int) this << endl;
#endif
	pthread_mutex_destroy(&_mutex);
#ifdef DEBUG_MUTEXES
	cout << "Thread " <<  (int) pthread_self().p << " destroyed mutex " << (int) this << endl;
#endif
}

void Mutex::lock(void)
{
#ifdef DEBUG_MUTEXES
	cout << "Thread " <<  (int) pthread_self().p << " locking mutex " << (int) this << endl;
#endif
    pthread_mutex_lock(&_mutex);
#ifdef DEBUG_MUTEXES
	cout << "Thread " <<  (int) pthread_self().p << " locked mutex " << (int) this << endl;
#endif
}

void Mutex::unlock(void)
{
#ifdef DEBUG_MUTEXES
	cout << "Thread " <<  pthread_self().p << " unlocking mutex " << (int) this << endl;
#endif
    pthread_mutex_unlock(&_mutex);
#ifdef DEBUG_MUTEXES
	cout << "Thread " <<  pthread_self().p << " unlocked mutex " << (int) this << endl;
#endif
}
