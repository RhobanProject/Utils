/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
#include "Player.h"

Player::Player() : animated_by_tick_machine(false)
{
};

void Player::init(double hertz, bool animated_by_tick_machine_)
{
    frequency = hertz;
    animated_by_tick_machine = animated_by_tick_machine_;
    use_locks = !animated_by_tick_machine;
    TickMachine::get_tick_machine()->register_timer(this);
}

void Player::tick()
{
    TM_DEBUG_MSG("Ticking player " << (int) this << " at frequency " << frequency);

    TickTimer::tick();

    if(animated_by_tick_machine)
    {
        try
        {
            if(try_play())
                step();
            else
                TM_DEBUG_MSG("Player " << (int) this << " at frequency " << frequency << " not running " << (suspended ? " suspended " : ""));
        }
        catch(string exc)
        {
            TM_CAUTION_MSG("TickMachine: stopping a player which has thrown the exception: "<<exc);
            stop();
        }
        catch(...)
        {
            TM_CAUTION_MSG("TickMachine: stopping a player which has thrown an exception.");
            stop();
        }
    }
}

Player::~Player()
{
}

