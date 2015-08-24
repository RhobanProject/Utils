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
 * TimedThread.hpp
 *
 *  Created on: 19 juil. 2011
 *      Author: Hugo
 */

#ifndef TIMED_THREAD_HPP_
#define TIMED_THREAD_HPP_

#include <timing/TickMachine.h>
#include <timing/Player.h>

#include <timing/chrono.h>
#include "Thread.h"

/*
 * Repeated task with small CPU consumption
 * are scheduled in a unique thread called the TickMachine
 *
 * the two following classes are the same
 * 'RepeatedLightweightTask' is probably a better name
 */
class TimedThread;
class RepeatedLightweightTask;


/*
 * RepeatedTask with possibly high CPU consumption
 * are scheduled in individual threads
 *
 * the two following classes are the same
 * 'RepeatedTask' is probably a better name
 *
 */
class SlowTimedThread;
class RepeatedTask;


/*
*		In a TimedThread a.k.a. RepeatedLightweightTask the running time of a call to step()
*       should be small (<1ms).
*
*       If the running time of the call to step() is large or unknown dont use TimedThread=RepeatedLighweightTask
*		but SlowTimedThread = RepeatedTask instead.
*
*       The reason is TimedThreads a.k.a. RepeatedLightweightTask are stepped one by one, one at a time
*		and in the meantime other RepeatedLightweightTasks are waiting
 */
using namespace Rhoban;

class TimedThread : public Player
{
protected:
	/* dont delete this, object, use dispose() instead. The TickMAchine will take care of the deletion in a separate thread. */
	virtual ~TimedThread(){};

public:
	TimedThread();

	/* delete the object asynchronously on the TickMachine thread. Equivalent to ~TimeThread(). */
	void dispose();

	/*!
	* @param frequency_
	* this sets the tick frequency and creates and starts the timed thread
	*
	* The TimedThread will be automatically animated and the step()
	*  method will be called at the given frequency
	*
	*/
	void init(double hertz);

	/*
	Sae as init but the thread is suspended on startup, use Playable::pplay() to start it */
	void init_suspended(double hertz, bool animate = true);

	/*
	 * This constructor avoid to use init(frequency)
	 */
	TimedThread(double frequency);

	/*!
	 * frequency can be changed using set_frequency() inherited from TickTimer
	 */

protected:
	/*!
	 * The action to perform between two ticks
	 * This method must be implemented in derived subclasses
	 */
	virtual void step()=0;

	Rhoban::Mutex mutex;
	void lock(){ mutex.lock(); }
	void unlock() { mutex.unlock(); }

};

class SlowTimedThread : protected Thread
{
public:
	SlowTimedThread();
	SlowTimedThread(double frequency);
	~SlowTimedThread();

	/*!
	 * @param frequency_
	 * this sets the tick frequency and creates and starts the timed thread
	 *
	 * The TimedThread will be automatically animated and the step()
	 *  method will be called at the given frequency
	 */
	//creates the thread and returns immediately
	void init(double hertz);
	//creates the thread paused and returns immediately
	void init_suspended(double hertz);
	//creates the thread, wait for it to be started, and returns
	void init_started(double hertz);

	/*!
	 * frequency can be changed using set_frequency()
	 */
	void set_frequency(double frequency);
	double get_frequency();

	/*
	 * stops the timed thread, and wait it to be dead if parameter is true
	 */
	void stop(bool wait_dead = false);

	/* waits for the thread to be finished */
	void wait_dead(){ Thread::wait_dead(); };

	/*
	 * the effective calling freauency of the timed thread
	 */
	double measured_frequency;
	double max_frequency;

	double elapsed_time_since_start();

protected:

	/*!
	 * The action to perform between two ticks
	 * This method must be implemented in derived subclasses
	 */
	virtual void step()=0;
	void execute();

private:
	Chrono start;


	//TickTimer timer;

};

class RepeatedLightweightTask : public TimedThread {};
class RepeatedTask : public SlowTimedThread {};

#endif /* TIMED_THREAD_HPP_ */
