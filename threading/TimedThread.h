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
         * this sets the tick frequency and creates and starts the timed thread
         *
         * The TimedThread will be automatically animated and the step() method will be called at the given frequency
         *
         * The running time of the call to step() should be quite small,
         * because in the meantime other TimedThreads are waiting
         *
         * If the running time of the call to step() is large, create a thread
         * and use a TickTimer instead
         *
         * @return
         */
        void init(double hertz);
        void init_suspended(double hertz);

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
