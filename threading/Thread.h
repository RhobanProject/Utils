/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
/**
  @file thread.h pthread implementation

  @author FLOWERS TEAM - Jérôme Béchu
  @date 01/2011

  @edited by Hugo Gimbert, RHOBAN Team:
  added suspend/resume functions, signal handling and control states
  @date 08/2011
*/

#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>

#include "Mutex.h"
#include "Condition.h"

namespace Rhoban
{

class Thread
{
public:
  Thread();
  virtual ~Thread();

  /**
   * start the thread
   * @param arg argument of the thread
   * @return phread_create value return
   */
  int start(void * arg = 0);

  /*!
   * Pause and resume,
   * to be called by another thread
   */
  void suspend_thread();
  void resume_thread();

  /*!
   * true iff the thread is suspended
   */
  virtual bool is_running();
  virtual bool is_suspended();
  virtual bool is_dead();
  virtual bool is_alive();


  /**
   * @brief kill the thread
   * 	Returns when the thread is in Dead state.
   *
   */
  virtual void kill();


  /*!
   * Wait for the thread to be started
   * returns from the moment the thread is setup and starts executing
   */
  void wait_started();

  void lock();
  void unlock();

  /* Attention, il ne faut pas imbriquer les sections critiques
   * l'utilisation de mutex récursifs résoudrait le problème mais ils sont buggués sur la mmnet
   */
#define BEGIN_THREAD_SAFE			\
  try						\
    {						\
  lock();


  #define BEGIN_SAFE(l)				\
  try						\
    {						\
  l.lock();

#define BEGIN_PSAFE(l)				\
try						\
  {						\
l->lock();

  //	  cout << "Locking " << #l << endl;

#define END_THREAD_SAFE					\
  unlock();						\
}							\
     catch(string & str)				\
       {						\
	 unlock();					\
	 throw str;					\
       }						\
     catch(...)						\
       {						\
	 unlock();					\
	 throw string("Unknown exception in thread");	\
       }

#define END_SAFE(l)					\
  l.unlock();						\
}							\
       catch(string & str)				\
	 {						\
	   l.unlock();					\
	   throw str;					\
	 }						\
       catch(...)					\
	 {						\
	   l.unlock();					\
	   throw string("Unknown exception in thread");	\
	 }

#define END_PSAFE(l)					\
  l->unlock();						\
}							\
       catch(string & str)				\
	 {						\
	   l->unlock();					\
	   throw str;					\
	 }						\
       catch(...)					\
	 {						\
	   l->unlock();					\
	   throw string("Unknown exception in thread");	\
	 }

  //		  cout << "Unlocking "<<  #l << endl;

protected:

  /*!
   * The state of the thread
   *
   * Before being started, the thread is Unborn
   * After start is caled, it is Starting until setup is over
   * then it is Running
   * Calling ask_for_suspend hangs the thread and put it in state Suspended
   * Calling ask_sor_resume puts it back to Running mode
   * Calling kill put in in Dying mode until the thread is over
   * then its state id Dead
   */

  typedef enum {Unborn,Starting,Running,Suspended,KillMe,Dying,Dead} ThreadState;
  ThreadState thread_state;

  /**
     @brief the common run of the thread
  */
  void run(void);

  /*
   * The id of the thread
   */
  int ThreadId(void);

  /**
   * starting point of the thread
   * @param CThread pointer
   * @return NULL
   */
  static void * EntryPoint(void* pthis);

  /**
   * method to setup the thread
   */
  virtual void setup(void);
  /**
   * thread core
   */
  virtual void execute(void)=0;
  void wait(void);


  /*!
   * Signal handling
   */
  static void block_signal(int signal);
  void wait_signal(int signal);

  /*!
   * pause if another thread asked to,
   * to be called by the current thread
   *
   * returns immediately if no other thread asked for suspend
   * otherwise waits for another thread to call ask_for _resume
   *
   * if lock is true, no other thread can pause this thread until
   * the Mutex pause_mutex is unlocked
   */
  void wait_for_resume(bool lock = false);

  pthread_t _Thread; ///< thread handle
  void * _Arg; ///< arguments

  Mutex pause_mutex;

  //Usable to interthread calls safe
  Mutex safe_mutex;

  Condition is_started;

};

}
#endif

