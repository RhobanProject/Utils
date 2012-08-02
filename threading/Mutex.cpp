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

#include "Mutex.h"

using namespace std;

Mutex::Mutex(void)
{
    pthread_mutex_init(&_mutex, NULL);
}

Mutex::~Mutex(void)
{
    pthread_mutex_destroy(&_mutex);
}

void Mutex::lock(void)
{
    pthread_mutex_lock(&_mutex);
}

void Mutex::unlock(void)
{
    pthread_mutex_unlock(&_mutex);
}
