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
disposed(false),
ticks_elapsed(0),
use_locks(true),
tick_counter(0),
frequency(0)
{
}



TickTimer::~TickTimer()
{
		unregister();
}

TickTimer::TickTimer(double hertz) :
    				ticks_elapsed(0),
    				relative(0),
    				use_locks(true),
    				tick_counter(0),
    				frequency(hertz)
{
	TickMachine::get_tick_machine()->register_timer(this);
}

TickTimer::TickTimer(double hertz, string name) :
    				timer_name(name),
    				ticks_elapsed(0),
    				relative(0),
    				use_locks(true),
    				tick_counter(0),
    				frequency(hertz)
{
	TickMachine::get_tick_machine()->register_timer(this);
}


/*! \brief Initializes the the variables before play. */
void TickTimer::prepare_play(bool forever, Rhoban::chrono durations)
{
	ticks_elapsed = 0;
	Playable::prepare_play(forever, durations);
}



void TickTimer::dispose()
{
	disposed = true;
	TickTimer * me = this;
	TickMachine::get_tick_machine()->dispose_timer(&me);
}

void TickTimer::unregister()
{
	if(!disposed)
	{
	TickMachine::get_tick_machine()->unregister_timer(this);
	}
	else
	{
		cout << "Skipping timer unregistration, cause timer is already deleted" << endl;
	}
}

void TickTimer::set_relative(Rhoban::chrono granularity)
{
	double gran = granularity.tv_sec + granularity.tv_usec/1000000.0;
	ui32 newrelative = (uint) floor( 1.0 / (gran * frequency) );
	if(newrelative<=0) newrelative=1;
	if( frequency < 0.0001)
		newrelative = 0;

	if(relative != newrelative)
	{
		relative = newrelative;
		tick_counter = relative;

		//for win32
		Rhoban::chrono now;
		gettimeofday(&now, NULL);

		int new_ticks_elapsed = (int) (1 + (to_secs(now ) - to_secs(start_time) ) * frequency);
		if(ticks_elapsed %2 == new_ticks_elapsed%2)
			ticks_elapsed = new_ticks_elapsed;
		else
			ticks_elapsed = new_ticks_elapsed + 1;
	}
	//	if(tick_counter > relative)tick_counter = relative;

}


bool TickTimer::is_tickable(Rhoban::chrono now)
{
    /*
    float now_secs = to_secs(now);
    float start_secs = to_secs(start_time);
    float elapsed = now_secs-start_secs;
    int elapsed_ticks = elapsed*frequency;
    int missed_ticks = elapsed_ticks - ticks_elapsed;
    */
	return (relative > 0) && ( (to_secs(now ) - to_secs(start_time) ) * frequency - ticks_elapsed >= 0);
}


/*! performs one tick
 * to be called by the tick machine */
void TickTimer::tick()
{
	TM_DEBUG_MSG("Ticking " << (long long int) this);
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
	TM_DEBUG_MSG("Ticking done " << (long long int) this);
}


/*!
 * wait for the next tick of the Player
 * to be called by the thread owning the timer
 */
void TickTimer::wait_next_tick()
{
	if(!use_locks)
		throw std::runtime_error("Wait_next_tick is not available for this player");

	if(relative == 0)
	{
		odd.lock();
		odd.unlock();
		even.lock();
		even.unlock();
	}
	else
	{
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
}

void TickTimer::wait_n_ticks(ui32 ticks_nb)
{
	for(unsigned int i = 0; i<ticks_nb; i++)
		wait_next_tick();
}


void TickTimer::set_frequency(double frequency_)
{
	frequency = frequency_;
	TickMachine::FrequencyChanged();
}

