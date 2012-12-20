/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
#ifndef TICKTIMER_H_
#define TICKTIMER_H_

#include <iostream>
#include <cstdlib>
#include <math.h>

class TickTimer;

#include "TickMachine.h"
#include "Playable.h"

using namespace std;

/*****************************************************************************
 * The TickMachine can
 * - either provide TickTimers to threads
 * - or schedule players at a regular frequency, players are objects with a step method
 *
 * Each timer is ticked at a regular frequency by the TickMachine
 * The frequency is chosen upon creation of the TickMachine::Player by
 * a call to create_tick_timer
 *
 * When calling the wait_next_tick() method of a timer,
 * the calling thread hangs until the next tick
 *
 * If a thread has to be animated at a given frequency,
 * it is recommended to use TimedThread.hpp
 *
 * Any object deriving from the Player class can be scheduled by the TickMachine.
 *****************************************************************************/
class TickTimer : public Playable
{
    friend class TickMachine;

    public:

    /*! 
     **************************************
     PUBLIC INTERFACE
     *****************************************/

    TickTimer(double hertz);
    virtual ~TickTimer();

    /*! \brief wait for the next tick of the MutexTimer
     *  to be called by the timed thread */
    virtual void wait_next_tick();
    virtual void wait_n_ticks(ui32 ticks_nb);

    /* change the frequency of the timer */
    void set_frequency(double hertz);

    /* get the real frequency of the timer */
    double get_frequency() const {return frequency;}

    bool is_tickable();

protected:


    /*! 
     **************************************
     the following fields and methods
     should only be accessed by the tick machine
     or superclasses
     *****************************************/

    /*! \brief computes the relative frequency */
    void set_relative();

    /*! \briefticks elapsed since the timer was started */
    int ticks_elapsed;

    /*! \brief the relative frequency */
    ui32 relative;

    /*! if true a claa to tick will lock/delock the mutexes
     * if false this will be ignored. this saves some cpu for players which do not need locks
     */
    bool use_locks;

    /*! \brief performs one tick to be called by the tick machine */
    virtual void tick();

    /*! ask the tick machine to kill and delete the timer
    */
    bool tm_kill_me;

    /*! \brief the internal tick counter */
    int tick_counter;

    TickTimer();


    /*! \brief the frequency of the task */
    double frequency;


    Mutex even;
    Mutex odd;
};

#endif // TICKTIMER_H_
