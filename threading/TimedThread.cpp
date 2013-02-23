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


void TimedThread::init(double hertz)
{
    forever = true;
    Player::init(hertz,true);
    play_state = playing;
}

TimedThread::TimedThread() { frequency = 1;};
TimedThread::TimedThread(double frequency){init(frequency);};
SlowTimedThread::SlowTimedThread(): timer(1){};
SlowTimedThread::SlowTimedThread(double frequency): timer(frequency){init(frequency);};

void SlowTimedThread::init(double hertz)
{
	timer.set_frequency(hertz);
	if(!is_alive())
		start(0);
}

void SlowTimedThread::init_suspended(double hertz)
{
	init(hertz);
	suspend_thread();
}

/*!
 * frequency can be changed using set_frequency()
 */
void SlowTimedThread::set_frequency(double frequency)
{
	timer.set_frequency(frequency);
}

/*
 * stops the timed thread
 */
void SlowTimedThread::stop()
{
	if(is_alive())
		kill();
}


void SlowTimedThread::execute()
{
	while(true)
	{
		step();
		timer.wait_next_tick();
	}
}

void TimedThread::init_suspended(double hertz)
{
    Player::init(hertz,true);
    gettimeofday( &suspend_start , 0);
    forever = true;

    play_state = suspended;
}

void TimedThread::kill_and_delete_me()
{
    tm_kill_me = true; 
}


