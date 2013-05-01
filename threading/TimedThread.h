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

#include "Thread.h"

/*
 *       * TimedThreads are stepped one by one, one at a time.
 *       * A step is a call to step()
         *
         * As a consequence, the running time of the call to step() should be quite small,
         * because in the meantime other TimedThreads are waiting
         *
         * If the running time of the call to step() is large,
         * dont use TimedThread but SlowTimedThread instead.
         */
using namespace Rhoban;

class TimedThread : public Player
{
protected:

	TimedThread();

	/*
	 * This constructors avoid to use init(frequency)
	 */
	TimedThread(double frequency);

    /*!
     * The action to perform between two ticks
     * This method must be implemented in derived subclasses
     */
    virtual void step()=0;

    public:

        /*!
         * @param frequency_
         * this sets the tick frequency and creates and starts the timed thread
         *
         * The TimedThread will be automatically animated and the step()
         *  method will be called at the given frequency
         *
         *
         */
        void init(double hertz);
        void init_suspended(double hertz);

        /*!
         * frequency can be changed using set_frequency() inherited from TickTimer
         */

    protected:
        /*!
         * asks the tick machine to kill the thread and delete it (and stop scheduling it of course)
         */
        void kill_and_delete_me();

        Rhoban::Mutex mutex;
        void lock(){ mutex.lock(); }
        void unlock() { mutex.unlock(); }

};

class SlowTimedThread : public Thread
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
     *
     *
     */
    void init(double hertz);
    void init_suspended(double hertz);

    /*!
     * frequency can be changed using set_frequency()
     */
    void set_frequency(double frequency);
    double get_frequency(){ return timer.get_frequency(); };

    /*
     * asynchronously stops the timed thread
     */
    void stop();

    /*
     * synchronously stops the timed thread
     * CALLING THIS FROM ANOTHER TIMED THREAD WILL RESULT IN DEADLOCK
     */
    virtual void kill();

    /*
     * the effective calling freauency of the timed thread
     */
    double measured_frequency;

protected:

    /*!
     * The action to perform between two ticks
     * This method must be implemented in derived subclasses
     */
    virtual void step()=0;
    void execute();

TickTimer timer;

};

#endif /* TIMED_THREAD_HPP_ */
