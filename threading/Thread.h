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
#include <logging/log.h>

#ifndef MSVC
#include <pthread.h>
#include <stdexcept>
#endif

#include "Mutex.h"
#include "Condition.h"

/**
 * MotorPrimitive log level
 * 1: Caution
 * 2: Message
 * 3: Debug
 */
#define TH_LOG_LEVEL 2

#define TH_CAUTION(...)     LOG_CPP(1, TH_LOG_LEVEL, "thread:caution", __VA_ARGS__)
#define TH_MSG(...)         LOG_CPP(2, TH_LOG_LEVEL, "thread", __VA_ARGS__)
#define TH_DEBUG(...)       LOG_CPP(3, TH_LOG_LEVEL, "thread:debug", __VA_ARGS__)

namespace Rhoban
{

class Thread
{

protected:
	/**
	* thread core
	*/
	virtual void execute() = 0;

	void lock();
	void unlock();

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

  std::string thread_name;

  /**
   * @brief kill the thread
   * 	Returns when the thread is in Dead state.
   *
   */
  virtual void kill();
  
  /**
   * Dettach the thread
   */
  virtual void detach();

  /*!
   * Wait for the thread to be started
   * returns from the moment the thread is setup and starts executing
   */
  Condition started;
  void wait_started();

  Condition dead;
  void wait_dead();


public:

  /* Attention, il ne faut pas imbriquer les sections critiques
   * l'utilisation de mutex récursifs résoudrait le problème mais ils sont buggués sur la mmnet
   */
#define BEGIN_THREAD_SAFE			\
  try						\
    {						\
	  TH_DEBUG("Thread " <<  Rhoban::Thread::currentThreadId() << " entering critical section") \
  lock(); \
  TH_DEBUG("Thread " <<  Rhoban::Thread::currentThreadId() << " has entered critical section");


#define BEGIN_SAFE(l)							\
  try									\
  {									\
    TH_DEBUG("Thread " <<  Rhoban::Thread::currentThreadId() << " entering critical section") \
    l.lock();								\
    TH_DEBUG("Thread " <<  Rhoban::Thread::currentThreadId() << " has entered critical section")
 
#define BEGIN_PSAFE(l)				\
  try						\
    {									\
	  TH_DEBUG("Thread " <<  Rhoban::Thread::currentThreadId() << " entering critical section") \
l->lock(); \
TH_DEBUG("Thread " <<  Rhoban::Thread::currentThreadId() << " has entered critical section")

  //	  cout << "Locking " << #l << endl;

#define END_THREAD_SAFE					\
  unlock();						\
  TH_DEBUG("Thread " <<  Rhoban::Thread::currentThreadId() << " has left critical section") \
}							\
     catch(std::exception & str)				\
       {						\
	 unlock();					\
	  TH_DEBUG("Thread " <<  Rhoban::Thread::currentThreadId() << " has left critical section") \
	 throw str;					\
       }						\
     catch(string & str)				\
       {						\
	 unlock();					\
	  TH_DEBUG("Thread " <<  Rhoban::Thread::currentThreadId() << " has left critical section") \
	 throw str;					\
       }						\
     catch(...)						\
       {						\
	 unlock();					\
	  TH_DEBUG("Thread " <<  Rhoban::Thread::currentThreadId() << " has left critical section") \
	 throw string("Unknown exception in thread");	\
       }

#define END_SAFE(l)					\
  l.unlock();						\
  TH_DEBUG("Thread " << Rhoban::Thread::currentThreadId() << " has left critical section") \
}							\
     catch(const std::runtime_error & str)				\
       {						\
	 l.unlock();					\
	  TH_DEBUG("Thread " <<  Rhoban::Thread::currentThreadId() << " has left critical section") \
	 throw str;					\
       }						\
     catch(const std::exception & str)				\
       {						\
	 l.unlock();					\
	  TH_DEBUG("Thread " <<  Rhoban::Thread::currentThreadId() << " has left critical section") \
	 throw str;					\
       }						\
       catch(const string & str)				\
	 {						\
	   l.unlock();					\
	   TH_DEBUG("Thread " <<  Rhoban::Thread::currentThreadId() << " has left critical section") \
	   throw str;					\
	 }						\
       catch(...)					\
	 {						\
	   l.unlock();					\
	   TH_DEBUG("Thread " <<  Rhoban::Thread::currentThreadId() << " has left critical section") \
	   throw string("Unknown exception in thread");	\
	 }

#define END_PSAFE(l)					\
  l->unlock();						\
  TH_DEBUG("Thread " <<  Rhoban::Thread::currentThreadId() << " has left critical section") \
}							\
       catch(string & str)				\
	 {						\
	   l->unlock();					\
	   TH_DEBUG("Thread " <<  Rhoban::Thread::currentThreadId() << " has left critical section") \
	   throw str;					\
	 }						\
	 catch (exception & e)				\
	   {						\
	   l->unlock();					\
	   TH_DEBUG("Thread " << Rhoban::Thread::currentThreadId() << " has left critical section") \
	   throw e;					\
	 }						\
	 catch (...)					\
	 {						\
	   l->unlock();					\
	   TH_DEBUG("Thread " <<  Rhoban::Thread::currentThreadId() << " has left critical section") \
	   throw string("Unknown exception in thread");	\
	 }

  //		  cout << "Unlocking "<<  #l << endl;
  
  /**
   * The id of the current thread
   */
  static int currentThreadId(void);

  /*
   * The id of the thread executing this object
   */
  int threadId(void){ return myId; }


    /**
     @brief the common run of the thread
  */
  void run(void);

protected:

  int myId;

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
   * starting point of the thread
   * @param CThread pointer
   * @return NULL
   */
#ifndef MSVC
  static void * EntryPoint(void* pthis);
#else
  static DWORD WINAPI EntryPoint(LPVOID pthis);
#endif
  /**
   * method to setup the thread
   */
  virtual void setup(void);

  /**
  * method to cleanup resources used by the thread when it stops or is killed
  */
  virtual void cleanup(void){};

  /* wait end of the thread */
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

#ifndef MSVC
  pthread_t _Thread; ///< thread handle
#else
  HANDLE _Thread;
#endif
  void * _Arg; ///< arguments

  Mutex pause_mutex;

  //Usable to interthread calls safe
  Mutex safe_mutex;

};

}
#endif

