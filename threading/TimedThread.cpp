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
#include <chrono.h>

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




double SlowTimedThread::elapsed_time_since_start()
{
	return now_chr.tv_sec - start_chr.tv_sec + (now_chr.tv_usec - start_chr.tv_usec) / 1000000.0;
}

void SlowTimedThread::execute()
{
	Rhoban::chrono last;
	Rhoban::chrono before;
	gettimeofday(&now_chr,NULL);
	gettimeofday(&start_chr, NULL);

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
		gettimeofday(&before,NULL);
		step();

		last = now_chr;
		gettimeofday(&now_chr,NULL);
		measured_frequency = 0.9 * measured_frequency + min( 1000.0 , 0.1 / ( now_chr.tv_sec - last.tv_sec + (now_chr.tv_usec - last.tv_usec) /1000000.0 ));

		double step_ms = 1000 * (now_chr.tv_sec - before.tv_sec) + (now_chr.tv_usec - before.tv_usec) /1000.0;
		int to_wait = 1000.0 / max_frequency - step_ms;

		//cout << "Max freq " << max_frequency << " step_ms " << step_ms << " waiting " << to_wait << endl;

		syst_wait_ms(max(1,to_wait));

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



