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
#include <queue>
#include <threading/Thread.h>
#include <threading/Mutex.h>
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

class TickMachine : public Rhoban::Thread
{
    friend class TickTimer;
    friend class Player;

    public:

    /*! The maximal possible schedule frequency in Hz */
    static const double min_frequency = 100.0;
    static const double max_frequency = 150.0;

    /*! \brief Start the tick machine. It is not mandatory to use this function
     *  however depending on the time the init procedure takes, it can be used
     *  at the beginning of operations. */
    static void init_tick_machine();

    /*! \brief Retrieve (and create if needed) the unique instance of the tick machine */
    static TickMachine * get_tick_machine();


    protected:

    /*************************************************************************/
    /*! main loop of the tick machine */
    /*************************************************************************/

    void execute();

    /*! \brief flag telling execute() to update timer parameters */
    bool timer_should_be_updated;

    /*! \brief alert the tick machien to change granularity */
	static void FrequencyChanged();

    /*! \brief flag telling execute() to update granularity */
	Rhoban::Mutex granularity_mutex;
    bool granularity_should_be_updated;

    /*! callled by execute: performs ticks on players that needs it
     *  and updates time_to_wait fields in players */
    void tick_players();




    /*! The constructor is protected
     *  use create tick machine instead. */

    TickMachine();
    virtual ~TickMachine();

    /*! \brief There is a unique instance of tick machine */
    static TickMachine * the_tick_machine;

    /*! \brief The procedure of starting the tick machine */
    static TickMachine * createTickMachine();

    /*! \brief the time granularity of the TickMachine */
    struct timeval granularity;

    /* The list of pending timers to be registered by execute()
     * We use a list because iterators remain valid when inserting/deleting elements
     */
    Rhoban::Mutex timers_to_register_list_mutex;
    list<TickTimer *> timers_to_register;
    bool timer_to_register;

    /* The list of pending timers to be unregistered by execute()
     * We use a list because iterators remain valid when inserting/deleting elements
     */
    Rhoban::Mutex timers_to_unregister_list_mutex;
    list<TickTimer *> timers_to_unregister;
    bool timer_to_unregister;

    /* The list of pending timers to be unregistered by execute()
     * We use a list because iterators remain valid when inserting/deleting elements
     */
    Rhoban::Mutex timers_to_delete_list_mutex;
    list<TickTimer *> timers_to_delete;
    bool timer_to_dispose;

    /*************************************************************************/
    // used by constructors and destructors of timers
    /*************************************************************************/

    /*! \brief the tick machine creates a mutex timer that
     * will tick at the given frequency. Use timer->wait_next_tick() to wait between two ticks*/
    void register_timer(TickTimer *);

    /*! \brief to clean up when the timer no longer used */
    void unregister_timer(TickTimer *);

    /*! \brief to delete when the timer is no longer used */
    void dispose_timer(TickTimer *);

    //for debug
    static timeval start_time;

#ifndef WIN32
    sigset_t block_set;
#endif


    /*! \brief to be called by the tick machine thread
     *  on arm-linux it is mandatory to do so because threads have different process ids
     *  thus a thread cannot influence signal reception of other threads */
    void update_timer();

    /*************************************************************************/
    // Players Management
    /*************************************************************************/

    /*! The players to time */
    list<TickTimer *> players;

    /*! \brief the setup of the underlying thread object */
    void setup(void) { set_granularity(granularity); };

    /*! sets time granularity
     * called at setup and by update_granularity_and_players() */
    void set_granularity(struct timeval interval);

    /*! updates time granularity of the machine,
     *  according to the frequencies of players
     *  also update intervals of players */
    void update_granularity_and_players(double pourcentage_erreur_relative = 10.0);

};

#endif // TICK_MACHINE_H_ 

