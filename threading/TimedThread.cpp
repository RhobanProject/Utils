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

/* dont delete this, object, use dispose() to dispose it */
void TimedThread::dispose()
{
	TickTimer::dispose();
}

TimedThread::TimedThread(double frequency){init(frequency);};

SlowTimedThread::SlowTimedThread(): timer(1,"SlowTimedThread"), measured_frequency(1)
{
};

SlowTimedThread::~SlowTimedThread()
{
	thread_state = Dead;
}

SlowTimedThread::SlowTimedThread(double frequency): timer(frequency)
{
	init(frequency);
}

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
 * asynchronously stops the timed thread
 *
 * We do not use Thread::kill() because join is blocking from another TimedThread
 *
 */
void SlowTimedThread::stop()
{
	if(is_alive())
	{
		wait_started();
		    thread_state = Dying;
	}
}

void SlowTimedThread::kill()
{
	Thread::kill();
}




void SlowTimedThread::execute()
{
	struct timeval now;
	gettimeofday(&now,NULL);

	while(thread_state != Dying && thread_state != Dead)
	{
		if(timer.get_frequency() < 0.00001)
			measured_frequency = 0;

		timer.wait_next_tick();

		step();

		struct timeval before = now;
		gettimeofday(&now,NULL);
		measured_frequency = 0.9 * measured_frequency + min( 1000.0 , 0.1 / ( now.tv_sec - before.tv_sec + (now.tv_usec - before.tv_usec) /1000000.0 ));

		//cout << /*TM_CAUTION_MSG*/ "Waiting nexttick in Timedthread " << this->ThreadId() << endl;
		//cout << /*TM_CAUTION_MSG*/ "Done Stepping Timedthread " << this->ThreadId() << endl;
	}
	thread_state = Dead;
}

void TimedThread::init_suspended(double hertz)
{
    Player::init(hertz,true);
    gettimeofday( &suspend_start , 0);
    forever = true;

    play_state = suspended;
}



