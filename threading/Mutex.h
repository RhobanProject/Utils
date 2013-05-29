/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>

#undef DEBUG_MUTEXES

namespace Rhoban
{
class Condition;

class Mutex
{
	friend class Condition;
public:
  Mutex(void);
  virtual ~Mutex(void);
  virtual void lock(void);
  virtual void unlock(void);

protected:
  pthread_mutex_t _mutex;
};
}
#endif

