/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
#ifndef PLAYABLE_H_
#define PLAYABLE_H_

#include <iostream>
#include <cstdlib>
#include <math.h>

class Playable;

#include "ticks.h"

using namespace std;

/*******************************************
 * A generic class for playable objects,
 * used by timedthreads and splines
 */
class Playable
{
    public:

        /*! \brief Note that the object is initially suspended */
        Playable();
        virtual ~Playable();

        virtual void play();
        virtual void play(timeval duration);
        virtual void play(ui32 msecs);
        virtual void play(double secs);
        virtual void suspend();
        virtual void resume();
        virtual void suspend_resume();
        virtual void stop();

        typedef enum
        {
            playing,
            suspended,
            stopped
        } PlayableStatus;

        PlayableStatus play_state;

        /*!
         * Called when the tick machine stops the object because playing duration is over
         */
        virtual void onStop();

        /*! \brief Checks whether the object is currently playing and not suspended. */
        virtual bool is_running();
        virtual bool is_suspended();
        virtual bool is_stopped();

        /*!
         * to be called each time something may happens to the object,
         * returns true iff the object can be played
         */
        bool try_play();

        string status();

        /*! \brief Time elapsed since last play start */
        double real_time;



        /*! \brief Time elapsed since the last reset */
        double since_last_reset();

        /*! resets the value last_reset */
        void reset();

        static void copy(Playable * src, Playable * dest);

        /*! \brief Time elapsed in suspended mode
         * thus the actual playing time is real_time - suspend_time
         */
        double suspend_time;

    protected:
        /*! \brief Initializes the the variables before play. */
        virtual void prepare_play(bool forever, timeval durations);

        /*! \brief Should the play be played forever? */
        bool forever;


        /*! \brief Start time. */
        struct timeval start_time;

        /*! last time update was performed. */
        struct timeval last_step_time;

        /*! \brief Stop time. */
        struct timeval stop_time;

        /*! last time update was performed. */
        struct timeval suspend_start;

        /*! \brief Last reset time. */
        struct timeval reset_time;

};

#endif // PLAYABLE_H_
