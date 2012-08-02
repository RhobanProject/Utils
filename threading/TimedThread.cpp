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
 * TimedThread.cpp
 *
 *  Created on: 19 juil. 2011
 *      Author: Hugo
 */

#include <iostream>

#include "ticks.h"
#include "TimedThread.h"

using namespace std;

TimedThread::TimedThread()
{
}

TimedThread::~TimedThread()
{
    kill();
}

void TimedThread::resume()
{
    Player::resume();
    resume_thread();
}

void TimedThread::suspend()
{
    Player::suspend();
    suspend_thread();
}

void TimedThread::init(double hertz, bool threaded)
{
    Player::init(hertz,!threaded);
    play_state = playing;
    forever = true;
    if(threaded)
    {
        start(0);
        wait_started();
    }
    else
    {
        thread_state = Running;
    }
}

void TimedThread::init_suspended(double hertz, bool threaded)
{
    pause_mutex.lock();
    Player::init(hertz,!threaded);
    forever = true;

    if(threaded)
    {
        start(0);
        wait_started();
    }
    thread_state = Suspended;
    play_state = suspended;
}

void TimedThread::execute()
{
    while(thread_state != Dying)
    {
        wait_for_resume(true);
        step();
        pause_mutex.unlock();
        wait_next_tick();
    }
}

void TimedThread::kill()
{
    wait_started();
#ifndef WIN32
    if(_Thread)
#else
        if(_Thread.p)
#endif
        {
            if(thread_state== Dead || thread_state == Dying) return;
            if(thread_state==Suspended)
            {
                TM_DEBUG_MSG("Resuming TimedThread before killing it");
                resume();
                thread_state = Dying;
            }
            else
            {
                thread_state=Dying;
            }
            TM_DEBUG_MSG("TimedThread dying, waiting to join...");
            pthread_join(_Thread, NULL);
#ifndef WIN32
            _Thread=0;
#else
            _Thread.p=0;
#endif
        }
    TM_DEBUG_MSG("TimedThread dead");
    thread_state = Dead;
}

void TimedThread::kill_and_delete_me()
{
    wait_started();
    tm_kill_me = true; 
}


