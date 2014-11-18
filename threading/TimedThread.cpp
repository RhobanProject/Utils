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
//#include <chrono.h>

using namespace std;


void TimedThread::init(double hertz)
{
    forever = true;
    Player::init(hertz,true);
    play_state = playing;
}

TimedThread::TimedThread() { frequency = 1;}

/* dont delete this, object, use dispose() to dispose it */
void TimedThread::dispose()
{
	TickTimer::dispose();
}

TimedThread::TimedThread(double frequency){init(frequency);}

/*
SlowTimedThread::SlowTimedThread(): timer(1,"SlowTimedThread"), measured_frequency(1)
{
};
*/
SlowTimedThread::SlowTimedThread(): measured_frequency(1)
{
	max_frequency = 0;
}


SlowTimedThread::~SlowTimedThread()
{
	kill();
}

/*
SlowTimedThread::SlowTimedThread(double frequency): timer(frequency)
{
	init(frequency);
}
*/

SlowTimedThread::SlowTimedThread(double frequency)
{
	max_frequency = frequency;
	init(frequency);
}

void SlowTimedThread::init(double hertz)
{
	//timer.set_frequency(hertz);
	max_frequency = hertz;
	if(!is_alive())
		Thread::start(0);
}

void SlowTimedThread::init_suspended(double hertz)
{
	init(hertz);
	suspend_thread();
}

void SlowTimedThread::init_started(double hertz)
{
	init(hertz);
	wait_started();
	start.reset();
}


/*!
 * frequency can be changed using set_frequency()
 */
void SlowTimedThread::set_frequency(double frequency)
{
	max_frequency = frequency;
	//timer.set_frequency(frequency);
}

double SlowTimedThread::get_frequency()
{
	return max_frequency;
}

/*
 * asynRhoban::chronously stops the timed thread
 *
 * We do not use Thread::kill() because join is blocking from another TimedThread
 *
 */
void SlowTimedThread::stop(bool wait)
{
	if(is_alive())
	{
		wait_started();
		    thread_state = Dying;
		if (wait)
			wait_dead();
	}
}





double SlowTimedThread::elapsed_time_since_start()
{
	return start.getTime();
}

void SlowTimedThread::execute()
{
	start.reset();
	Chrono last, before;

	while(thread_state != Dying && thread_state != Dead)
	{
	//	if(timer.get_frequency() < 0.00001)
		//	measured_frequency = 0;

		while(max_frequency < 0.00001)
		{
			measured_frequency = 0;
			syst_wait_ms(1000);
		}

		//timer.wait_next_tick();
		before.reset();

		step();

		double t = last.getTime();
		measured_frequency = 0.9 * measured_frequency + 0.1 / min(1000.0, t);


		last.reset();

		double t2 = before.getTimeUsec();
		int to_wait = max(1.0, 1000000.0 / max_frequency - t2);

		//cout << "Max freq " << max_frequency << " step_ms " << step_ms << " waiting " << to_wait << endl;

		syst_wait_us(to_wait);

		//cout << /*TM_CAUTION_MSG*/ "Waiting nexttick in Timedthread " << this->ThreadId() << endl;
		//cout << /*TM_CAUTION_MSG*/ "Done Stepping Timedthread " << this->ThreadId() << endl;
	}
	//not yet thread_state = Dead;
}

void TimedThread::init_suspended(double hertz)
{
    Player::init(hertz,true);
    gettimeofday( &suspend_start , 0);
    forever = true;

    play_state = suspended;
}



