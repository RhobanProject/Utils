/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
#include "Playable.h"
#include "TickMachine.h"

void Playable::play()
{
    timeval ttl = {0,0};
    prepare_play(true,ttl);
    resume();
}

void Playable::play(timeval duration)
{
    prepare_play(false,duration);
    resume();
}

void Playable::play(ui32 msecs)
{
    timeval duration;
    duration.tv_sec = msecs/1000;
    duration.tv_usec = (msecs % 1000) * 1000;
    play(duration);
}

void Playable::play(double secs)
{
    timeval duration;
    duration.tv_sec = (long) floor(secs);
    duration.tv_usec = (ui32) ( (secs - duration.tv_sec) * 1000000);
    play(duration);
}

void Playable::copy(Playable * src, Playable * dest)
{
    if( ! src || ! dest)
        throw string("Cannot copy null playable");
    dest->play_state = src->play_state;
    dest->real_time = src->real_time;
    dest->suspend_time = src->suspend_time;
    dest->forever = src->forever;
    dest->start_time = src->start_time;
    dest->last_step_time = src->last_step_time;
    dest->stop_time = src->stop_time;
    dest->suspend_start = src->suspend_start;
    dest->reset_time = src->reset_time;
}

void Playable::suspend()
{
    TM_DEBUG_MSG("Suspending player");
    if(!is_suspended())
        gettimeofday(&suspend_start,0);

    play_state = suspended;
}

void Playable::resume()
{
    TM_DEBUG_MSG("Resuming player");
    if(is_suspended())
    {
        struct timeval now;
        gettimeofday( &now , 0);
        decrease(now, suspend_start);
        suspend_time += to_secs(now);
        play_state = playing;
    }
}

void Playable::suspend_resume()
{
    if(!is_suspended())
        suspend();
    else
        resume();
}

void Playable::stop()
{
    TM_DEBUG_MSG("Stopping player");
    onStop();
    forever = false;
    play_state = stopped;
}

void Playable::onStop()
{

}

bool Playable::is_running()
{
    if(is_suspended())
        return false;
    if(forever)
        return true;
    timeval time_to_live = stop_time;
    timeval now;
    gettimeofday(&now,0);
    decrease(time_to_live,now);
    if(1000000 * time_to_live.tv_sec + time_to_live.tv_usec > 0)
        return true;
    else
    {
        onStop();
        play_state = stopped;
        return false;
    }
}

bool Playable::try_play()
{
    if(is_running())
    {
        gettimeofday(&last_step_time , 0);
        timeval now = last_step_time;
        decrease(now, start_time);
        double new_real_time = to_secs(now);
        real_time = new_real_time - suspend_time;
        return true;
    }
    else
    {
        return false;
    }
}


void Playable::reset()
{
    gettimeofday(&reset_time,0);
}

double Playable::since_last_reset()
{
    timeval now;
    gettimeofday(&now,0);
    decrease(now, reset_time);
    return to_secs(now);
}

string Playable::status()
{
    std::ostringstream s;

    if(is_suspended())
        s << "[suspended] since " << real_time - to_secs(suspend_start);
    else if(is_running())
        s << "[playing]";
    else
        s << "[stopped]";

    s << " suspend time " << suspend_time;

    return s.str();

}

bool Playable::is_suspended()
{
    return (play_state == suspended) || (play_state == stopped);
}

bool Playable::is_stopped()
{
    return (play_state == stopped);
}

Playable::Playable()
{
    gettimeofday(&start_time,0);
    gettimeofday(&stop_time,0);
    gettimeofday(&last_step_time,0);
    real_time = 0;
    play_state = playing;
    suspend_time = 0;
}

void Playable::prepare_play(bool forever_, timeval duration_)
{
    forever = forever_;

    real_time = suspend_time = 0;

    gettimeofday(&start_time,0);
    last_step_time = suspend_start = stop_time = start_time;

    increase(stop_time, duration_);
    reset();
}

Playable::~Playable()
{
}

