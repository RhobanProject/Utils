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
 * TickMachine.h
 *
 *  Created on: 19 juil. 2011
 *      Author: hugo
 */
#ifndef TICK_MACHINE_H_
#define TICK_MACHINE_H_

#include <time.h>
#ifndef WIN32
#include <sys/time.h>
#endif
#include <signal.h>
#include <vector>
#include <list>
#include <string>
#include "types.h"
#include "Thread.h"
#include "Mutex.h"
#ifdef _WIN32
#include <windows.h>
#endif

class TickTimer;
class Player;
class TickMachine;

#include "TickTimer.h"

using namespace std;

/*****************************************************************************/
#define TM_CAUTION_MSG(msg) { cout << "TM CAUTION: " << msg << endl << flush; }
#define TM_DEBUG 0
#if TM_DEBUG==1
#define TM_DEBUG_MSG(msg) { timeval now; gettimeofday(&now,0); cout << "TM DEBUG " <<to_secs(now) - to_secs(TickMachine::start_time)<< " :"<< msg << endl << flush;  }
#else
#define TM_DEBUG_MSG(msg) {}
#endif
/*****************************************************************************/

class TickMachine : public Thread
{
    friend class TickTimer;
    friend class Player;

    public:

    /*! The maximal possible schedule frequency in Hz */
    static const double min_frequency = 100.0;
    static const double max_frequency = 150.0;

    /*! \brief the time granularity of the TickMachine */
    struct timeval granularity;

    /*************************************************************************/
    // As the TickMachine is a singleton, the API is mainly static.
    /*************************************************************************/
    public:

    /*! \brief Start the tick machine. It is not mandatory to use this function
     *  however depending on the time the init procedure takes, it can be used
     *  at the beginning of operations. */
    static void init_tick_machine();

    /*! \brief Retrieve (and create if needed) the unique instance of the tick machine */
    static TickMachine * get_tick_machine();

    //for debug
    static timeval start_time;

    /*************************************************************************/
    /*! main loop of the tick machine */
    /*************************************************************************/

    protected:

    void execute();

    /*************************************************************************/
    /*! singleton stuff */
    /*************************************************************************/

    private:

    /*! The constructor is protected
     *  use create tick machine instead. */

    TickMachine();
    virtual ~TickMachine();

    /*! \brief There is a unique instance of tick machine */
    static TickMachine * the_tick_machine;

    /*! \brief The procedure of starting the tick machine */
    static TickMachine * createTickMachine();

    /*! \brief internally register/unregister a timer*/
    void internal_register_timer(TickTimer * timer);
    void internal_unregister_timer(TickTimer * timer);

    /*! \brief see change_frequency for doc. */
    void internal_change_frequency(TickTimer *, double hertz);

    /*! \brief Halts the tick machine for one tick */
    virtual void wait_next_tick();

    /*! This mutex is used to restrict access to public methods
     *  to the moments where the TickMachine is idle. */
    Mutex safe;

    /*************************************************************************/
    // used by constructors and destructors of timers
    /*************************************************************************/

    /*! \brief the tick machine creates a mutex timer that
     * will tick at the given frequency. Use timer->wait_next_tick() to wait between two ticks*/
    static void register_timer(TickTimer *, double hertz);

    /*! \brief to clean up when a timed mutex is no longer used */
    static void unregister_timer(TickTimer *);

    /*! \brief changes the frequency to be called by a timed thread
     *  the tick machine will create two mutexes that it will lock alternatively */
    static void change_frequency(TickTimer *, double hertz);
    /*************************************************************************/



#ifndef WIN32
    sigset_t block_set;
#endif


    /*! \brief flag telling the tick machine to update timer parameters */
    bool timer_should_be_updated;

    /*! \brief to be called by the tick machine thread
     *  on arm-linux it is mandatory to do so because threads have different process ids
     *  thus a thread cannot influence signal reception of other threads */
    void update_timer();

    /*************************************************************************/
    // Players Management
    /*************************************************************************/

    /*! The players to time */
    list<TickTimer *> players;

    TickTimer * to_kill;

    /*! sets time granularity */
    void set_granularity(struct timeval interval);

    /*! \brief the setup of the underlying thread object */
    void setup(void) { set_granularity(granularity); };

    /*! updates time granularity of the machine,
     *  according to the frequencies of players
     *  also update intervals of players */
    void update_granularity_and_players(double pourcentage_erreur_relative = 10.0);

    /*! performs ticks on players that needs it
     *  and updates time_to_wait fields in players */
    void tick_players();

};

#endif // TICK_MACHINE_H_ 

