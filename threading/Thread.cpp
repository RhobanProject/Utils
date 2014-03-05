/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
#include <iostream>
#ifndef MSVC
#include <unistd.h>
#else
#include "windows.h"
#endif
#include <stdio.h>
#include <signal.h>
#include "Thread.h"

using namespace std;
using namespace Rhoban;

Thread::Thread()
{
    thread_state = Unborn;
#ifndef WIN32
    _Thread = 0;
#else
#ifndef MSVC
    _Thread.p =0;
#endif
#endif
}

Thread::~Thread()
{
    try
    {
        if(thread_state != Dead)
        {
	  kill();
	}
        thread_state = Dead;
    }
    catch(char * err)
    {
        cerr << "Exception '"<<err<<"' when killing thread "<< this<<endl;
    }
    catch(string err)
    {
        cerr << "Exception '"<<err<<"' when killing thread "<< this<<endl;
    }
    catch(...)
    {
        cerr << "Exception when killing thread "<< this<<endl;
    };
}

void Thread::detach()
{
#ifndef MSVC
    pthread_detach(_Thread);
#endif
}

int Thread::start(void * arg)
{
    thread_state = Starting;
    _Arg = arg; 
#ifndef MSVC
    int code = pthread_create(&_Thread, NULL, Thread::EntryPoint, this);

    if (code != 0) {
        perror("pthread");
    }
    return code;
#else
	DWORD id;
	_Thread = CreateThread( 
            NULL,                   // default security attributes
            0,                      // use default stack size  
			Thread::EntryPoint,          // argument to thread function ,
			this,
            0,                      // use default creation flags 
            &id);   // returns the thread identifier 
	return 0;
#endif
	started.broadcast();
}

/*!
 * Pause and resume,
 * to be called by another thread
 */
void Thread::suspend_thread()
{
    wait_started();
    thread_state = Suspended;
    pause_mutex.lock();
}

void Thread::resume_thread()
{
    wait_started();
    pause_mutex.unlock();
    thread_state = Running;
}

/*!
 * true iff the thread is suspended
 */
bool Thread::is_suspended()
{
    wait_started();
    return thread_state==Suspended;
}

bool Thread::is_running()
{
    wait_started();
    return thread_state==Running;
}

bool Thread::is_dead()
{
    wait_started();
    return thread_state==Dead;
}

bool Thread::is_alive()
{
    return thread_state!=Dead && thread_state != Unborn && thread_state != Dying;
}

/*!
 * pause if another thread asked to,
 * to be called by the current thread
 *
 * returns immediately if no other thread asked for suspend
 * otherwise waits for another thread to call ask_for _resume
 */
void Thread::wait_for_resume(bool lock)
{
    wait_started();
    pause_mutex.lock();
    if(!lock) {
        pause_mutex.unlock();
    }

    if(thread_state == Suspended) {
        thread_state = Running;
    }
}


void Thread::kill(void)
{
	    if(!is_alive()) return;
    wait_started();
    thread_state = Dying;
	cleanup();

#ifndef MSVC
#ifndef WIN32
    if(_Thread)
#else
        if(_Thread.p)
#endif
        {
            pthread_cancel(_Thread);
            pthread_join(_Thread, NULL);
#ifndef WIN32
            _Thread=0;
#else
            _Thread.p=0;
#endif
		}
#else
	TerminateThread(_Thread,0);
#endif

	dead.lock();
	dead.broadcast();
	thread_state = Dead;
	dead.unlock();
  
}

int Thread::currentThreadId(void)
{
#ifdef WIN32
#ifndef MSVC
	return (int) pthread_self().p;
#else
	return GetCurrentThreadId();
#endif
#else
	return (long int) pthread_self();
#endif
}

void Thread::run(void)
{
    stringstream ss;
    ss << currentThreadId();
    thread_name = ss.str();

    myId = currentThreadId();

    try {
        started.lock();
        setup();
        thread_state = Running;
        started.broadcast();
        started.unlock();
        execute();
    } catch (int code) {
        cerr<<"Exception "<< code << std::endl;
    } catch (string exc) {
        cerr << "Exception in thread " << thread_name <<" :"<< exc<< endl;
    }

	cleanup();

	dead.lock();
	dead.broadcast();
	thread_state = Dead;
	dead.unlock();
}

#ifndef MSVC
 void * Thread::EntryPoint(void* pthis)
{
    Thread *pt = (Thread*)pthis;
    int s = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

    if (s != 0) {
        string err = "pthread_setcancelstate error";
        cerr << err;
        throw err;
    }

    s = pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    if (s != 0) {
        string err = "pthread_setcanceltype error";
        cerr << err;
        throw err;
    }

 #else
 DWORD Thread::EntryPoint(LPVOID pthis)
	 {

    Thread *pt = (Thread*)pthis;

#endif

	    pt->run();

#ifdef MSVC
		ExitThread(0);
#endif

    return NULL;
}


void Thread::setup(void)
{
}

/*!
 * Wait for the thread to be started
 */
void Thread::wait_started()
{
	//Hugo: We should use a condion instead
#ifdef WIN32
	started.lock();
	if(thread_state == Unborn || thread_state == Starting)
		started.wait();
	started.unlock();
#else
	while (thread_state == Unborn || thread_state == Starting)
        usleep(1000);
#endif
}

void Thread::wait_dead()
{
	dead.lock();
	dead.wait();
	dead.unlock();
}

void Thread::lock()
{
    safe_mutex.lock();
}
void Thread::unlock()
{
    safe_mutex.unlock();
}

void Thread::wait(void)
{
#ifndef MSVC
    pthread_join (_Thread, NULL);
#else
	wait_dead();
#endif
}

/*!
 * Signal handling
 */
void Thread::block_signal(int signal)
{
#ifndef WIN32
    sigset_t signal_mask;
    sigemptyset (&signal_mask);
    sigaddset (&signal_mask, signal);
    sigprocmask(SIG_BLOCK,&signal_mask,NULL);
    pthread_sigmask(SIG_BLOCK, &signal_mask, NULL);
#endif
}

void Thread::wait_signal(int signal)
{
#ifndef WIN32
    sigset_t signal_mask;
    sigemptyset (&signal_mask);
    sigaddset (&signal_mask, signal);
    int sig;
    sigwait(&signal_mask,&sig);
#endif
}


