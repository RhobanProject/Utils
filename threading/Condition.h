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

class Condition
{
public:

  Condition();
  ~Condition();

  // wait for the condition to be brodcasted (optional timeout in ms)
  int wait(Mutex *mutex, unsigned int timeout = 0);
  
  // broadcast a condition
  void broadcast();

private:

  pthread_cond_t condition;
};

#endif // _CONDITION_H
