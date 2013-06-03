/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>
#include <cstdlib>

class Player;

#include "TickMachine.h"
#include "TickTimer.h"

using namespace std;

/*****************************************************************************
 * Players are runnable objects that make a step at a fixed frequnecy,
 * following ticks of the tick machine
 *
 * Players can either be ticked:
 *
 *  directly by the tick machine which call the step method at regular intervals
 *  this should be done only when step execute in a short time and is bugfree
 *  otherwise this would hangs all the objects and threads ticked by the tick machine
 *  if the step function throws an exception, the object is not stepped anymore
 *
 *  or undirectly in this case the object can be ticked from another threads
 *  using calls to TickMachine::Player::wait_next_tick
 *  it is safer to use indirect scheduling if the thread can take a long time
 *  to step
 *****************************************************************************/
class Player : public TickTimer
{

    public:
        /*! \brief Note that the object is initially suspended */
        Player();
        virtual ~Player();

        /*! This creates and starts the timer at the given frequency
         *  if animated_by_tick_machine is true, the object will be ticked automatically by the tick machine
         *  otherwise, the object can be ticked by someone else using the TickTimer::wait_next_tick() method.
         *
         *  */
        virtual void init(double hertz, bool animated_by_tick_machine);

        /*! \brief the function to perform at each tick. */
        virtual void step() =0;

    protected:
        //if true each call to tick will rise a call to step()
        bool animated_by_tick_machine;

        void tick();

};

#endif // PLAYER_H_
