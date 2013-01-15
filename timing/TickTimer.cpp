/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
#include "TickTimer.h"

TickTimer::TickTimer() :
ticks_elapsed(0),
use_locks(true),
tm_kill_me(false),
tick_counter(0),
frequency(0)
{
}



TickTimer::~TickTimer()
{
	TM_DEBUG_MSG("TickTimer destructor: unregistering...");
	TickMachine::unregister_timer(this);
	TM_DEBUG_MSG("TickTimer destructor: unregistered");
}

TickTimer::TickTimer(double hertz) :
    		ticks_elapsed(0),
    		use_locks(true),
    		tm_kill_me(false),
    		tick_counter(0),
    		frequency(hertz)
{
	TickMachine::register_timer(this, hertz);
}


/*! \brief Initializes the the variables before play. */
void TickTimer::prepare_play(bool forever, timeval durations)
{
	ticks_elapsed = 0;
	Playable::prepare_play(forever, durations);
}

void TickTimer::set_relative()
{
	TickMachine * machine = TickMachine::get_tick_machine();
	double gran = machine->granularity.tv_sec + machine->granularity.tv_usec/1000000.0;
	relative = (uint) floor( 1.0 / (gran * frequency) );
	if(relative<=0) relative=1;
	tick_counter = relative;
}

bool TickTimer::is_tickable(timeval now)
{
	return (to_secs(now ) - to_secs(start_time) ) * frequency - ticks_elapsed >= 0;
}


/*! performs one tick
 * to be called by the tick machine */
void TickTimer::tick()
{
	//reinitializes the counter
	tick_counter = relative;

	//tick update is performed whtever state the object is in
	//so we dont care about return value
	try_play();

	if(!use_locks)
	{
		ticks_elapsed++;
		return;
	}
	else
	{
		//takes care of mutexes
		if(ticks_elapsed%2)
		{
			even.lock();
			ticks_elapsed++;
			odd.unlock();
		}
		else
		{
			odd.lock();
			ticks_elapsed++;
			even.unlock();
		}
	}
	//next_tick_date = now;
	//increase(next_tick_date, tick_interval);
}


/*!
 * wait for the next tick of the Player
 * to be called by the thread owning the timer
 */
void TickTimer::wait_next_tick()
{
	if(!use_locks)
		throw string("Wait_next_tick is not available for this player");

	if(ticks_elapsed%2)
	{
		odd.lock();
		odd.unlock();
	}
	else
	{
		even.lock();
		even.unlock();
	}
}

void TickTimer::wait_n_ticks(ui32 ticks_nb)
{
	for(unsigned int i = 0; i<ticks_nb; i++)
		wait_next_tick();
}


void TickTimer::set_frequency(double frequency_)
{
	frequency = frequency_;
	TickMachine::get_tick_machine()->change_frequency(this, frequency);
}

