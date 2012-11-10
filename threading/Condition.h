/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
#ifndef _CONDITION_H
#define _CONDITION_H

#include "Mutex.h"


/* Hugo I inherit agin from Mutex because
 * The effect of using more than one mutex for concurrent pthread_cond_timedwait() or pthread_cond_wait() operations on the same condition variable is undefined; that is, a condition variable becomes bound to a unique mutex when a thread waits on the condition variable, and this (dynamic) binding shall end when the wait returns.
 *
 */

class Condition : public Mutex
{
public:

  Condition();
  ~Condition();

  // wait for the condition to be brodcasted (optional timeout in ms)
  //the condition should be locked before use
  int wait(unsigned int timeout = 0);
  
  //wait for the condition with a particular Mutex
  int wait(Mutex * mutex, unsigned int timeout = 0);

  // broadcast a condition
  void broadcast();

private:

  pthread_cond_t condition;
};

#endif // _CONDITION_H
