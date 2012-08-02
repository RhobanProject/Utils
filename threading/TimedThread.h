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

#include "TickMachine.h"
#include "Player.h"

#include "Thread.h"
#include "Mutex.h"

class TimedThread : public Thread, public Player
{
    public:
        /*!
         * after the construction, the thread is not started yet
         */
        TimedThread();
        virtual ~TimedThread();

        /*suspend and resume the thread*/
        virtual void suspend();
        virtual void resume();

        /*!
         * @param frequency_
         * this sets the tick frequency and creates and starts the thread
         *
         * depending on the boolean
         * this will create or not a new thread
         *
         *in case a thread is not created, the tick machine will animate the TimedThread
         *in this case the running time of the call to step() should be very small,
         *because in the meantime other threads animated by the tick machine are waiting
         *
         * @return
         */
        void init(double hertz, bool threaded);
        void init_suspended(double hertz, bool threaded);

        /*!
         * frequency can be changed using set_frequency() inherited from TickTimer
         */

        /*!
         * Puts the thread in dying mode and waits for the thread to
         * execute its last step and then die.
         *
         * Returns when the thread is in Dead state.
         */
        virtual void kill();


    protected:
        /*!
         * asks the tick machine to kill the thread and delete it (and stop scheduling it of course)
         */
        void kill_and_delete_me();

        /*!
         * The action to perform between two ticks
         */
        virtual void step()=0;

        /*!
         * The core of the thread
         */
        void execute();

};

#endif /* TIMED_THREAD_HPP_ */
