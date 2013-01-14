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

using namespace std;


void TimedThread::init(double hertz)
{
    Player::init(hertz,true);
    play_state = playing;
    forever = true;
}

void TimedThread::init_suspended(double hertz)
{
    Player::init(hertz,true);
    gettimeofday( &suspend_start , 0);
    forever = true;

    play_state = suspended;
}

void TimedThread::kill_and_delete_me()
{
    tm_kill_me = true; 
}


