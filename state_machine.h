/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
/*****************************************************************************
 *  \file    state_machine.h
 *  \author  Hugo Gimbert - Olivier Ly
 *  \date    2010-12
 *
 *  \brief   State machine infrastructure.
 *****************************************************************************/
#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H
#include <stdlib.h>
#include <stdio.h>
#include <list>
#include <map>
#include <string>

// TODO: melance father s_father !!!

/*****************************************************************************/

#define TICK_FREQUENCY_DEFAULT 20

/*****************************************************************************/
// Request system
// The request system can be use to make state machine communicate with
// external module.
/*****************************************************************************/

template<typename requesttyp, typename datatyp> 
class RequestChannel {
public:
  std::list< std::pair< requesttyp, datatyp > > request_queue;
  bool queue_or_single;
public:
  RequestChannel(bool mem_mode) : queue_or_single(mem_mode) {};

  /* configure the request as a queue */
  void queue_mode() { queue_or_single = true; };

  /* configure the request channel as single (each new request delete the previous ones) */
  void single_mode() { queue_or_single = false; };

  void set_memory_mode (bool mode) { queue_or_single = mode; };

  void send_request( requesttyp r, datatyp d ) {
    if (!queue_or_single) request_queue.clear();
    request_queue.push_back(std::pair< requesttyp, datatyp > (r,d));
  };
  
  bool eat_request( requesttyp r, datatyp * d ) {
    if (request_queue.size() == 0) return false;
    if (request_queue.front().first != r) return false;
    if (d != NULL) *d = request_queue.front().second;
    request_queue.pop_front();
    return true;
  };

  bool is_request (requesttyp r) {
    if (request_queue.size() == 0) return false;
    return ( request_queue.front().first == r );
  };

  void pop_request () {
    if (request_queue.size() > 0) request_queue.pop_front();
  };
};

template<typename requesttyp>
class VoidRequestChannel : public RequestChannel<requesttyp, char> /* char is fake */ {
public:
  VoidRequestChannel(bool mem_mode) : RequestChannel<requesttyp, char>(mem_mode) {};
  void send_request( requesttyp r ) { RequestChannel<requesttyp, char>::send_request(r,1); };
  bool eat_request( requesttyp r ) { return RequestChannel<requesttyp, char>::eat_request(r,NULL); };
};

#define VOID_REQUEST_CHANNEL_BY_ENUM(chan_id, lst,...)      \
  typedef enum { lst, ... } chan_id ## _ENUM;                   \
  typedef VoidRequestChannel<chan_id ## _ENUM> chan_id;               

/*****************************************************************************/
class State;
/*****************************************************************************/

class StateMachine {
 private:
  bool debug;
  int transition_delay;
 public:
  void delay_transition(int ms) { 
    int tick_nb = (ms * frequency) / 1000;
    transition_delay = (tick_nb > 0)? tick_nb : 0; 
  }

  virtual std::string get_machine_id() = 0;

 public:
  State * init_state;
  State * active_state;
  State * next_state;
  int frequency;

  void set_debug(bool debug_mode) { debug = debug_mode; };
  bool debug_mode() { return debug; };

  StateMachine();

  /*! \brief internal initialization procedure. The requested point
   *  is that it must define the init_state. */
  virtual void init() = 0;

  /*! \brief this is an action done at the beginning of the machine */
  virtual void entry() = 0;

  /*! \brief this is an action done at every tic at every state */
  virtual void activity() = 0;

  /*! \brief this is an action done at the end of the machine */
  virtual void quit() = 0;

  /*! \brief global top priority transitions */
  virtual State * transition() = 0;

  /*! \brief start the machine. The init_state must have been defined. Note
   *  that this function is called by the constructor.
   *  \return 1 if ok, 0 otherwise. */
  int reset();

  /*! \brief the general scheduling function of the machine.
   *  \return 0 if the machine reached a terminal state. 1 if the machine
   *  is still running (RAS). -1 if active_state==NULL. */
  int tic();
};

/*****************************************************************************/

class State {
  int wait_n_tick;
 public:
  bool active;
  bool intern_is_active() {
    return active;
  };
  void intern_set_active(bool active_or_not) {
    active = active_or_not;
  };

  StateMachine * father; 

 State() : wait_n_tick(0), father(NULL) {};
 
  bool is_sys_wait_msing() { 
    if (wait_n_tick == 0) return false; 
    else wait_n_tick--; 
    return true; 
  }
  void sys_wait_ms_tick(int ms) { 
    if (father == NULL) return;
    int tick_nb = (ms * father->frequency) / 1000;
    wait_n_tick = (tick_nb > 0)? tick_nb : 0; 
  }
  bool ready() { return (wait_n_tick == 0); }

  virtual bool terminal() = 0;
  virtual void entry() = 0;
  virtual void activity() = 0;
  virtual void quit() = 0;
  virtual State * transition() = 0;

  virtual std::string get_state_id() = 0;
};

/*****************************************************************************/

#define DECLARE_STATE(StateName)                        \
  class StateName : public State {                      \
    static std::string state_id;                        \
    static StateMachine * s_father;                     \
    static State * singleton;                           \
  public:                                               \
    static bool is_active() {                           \
      return get_instance()->intern_is_active();        \
    };                                                  \
    static void set_active(bool active_or_not) {        \
      get_instance()->intern_set_active(active_or_not); \
    };                                                  \
    static State * get_instance() {		        \
      if (singleton==NULL)    {                         \
        singleton = new StateName();                    \
        singleton->father = s_father;                   \
      }                                                 \
      return singleton;                                 \
    }                                                   \
    bool terminal();                                    \
    void entry();                                       \
    void activity();                                    \
    void quit();                                        \
    State * transition();                               \
    std::string get_state_id() {                        \
      return state_id;                                  \
    };                                                  \
  };

#define STATE_GENERIC_CODE(FatherMachine,StateName)     \
  State * StateName::singleton = NULL;                  \
  StateMachine * StateName::s_father = FatherMachine;   \
  std::string StateName::state_id = #StateName;        

#define TRANSITION(cond, target)                \
  if (cond) { return target::get_instance(); }

#define ACTION_TRANSITION(cond, target, action) \
  if (cond) { action; return target::get_instance(); }

#define DELAYED_TRANSITION(cond, target, time)       \
  if (cond) { father->delay_transition(time); return target::get_instance(); }

#define ACTION_DELAYED_TRANSITION(cond, target, time, action)                  \
  if (cond) { father->delay_transition(time); action; return target::get_instance(); }

#define DIRECT_TRANSITION(target)               \
  return target::get_instance();

#define JUMP(target)                            \
  return target::get_instance();


#define DECLARE_MACHINE(MachineName, InitState) \
  class MachineName : public StateMachine {     \
  public:                                       \
    static std::string machine_id;              \
    void init() {                               \
      init_state = InitState::get_instance();   \
    };                                          \
    void entry();                               \
    void activity();                            \
    void quit();                                \
    State * transition();                       \
    std::string get_machine_id() {              \
      return machine_id;                        \
    };                                          \
  };

#define MACHINE_GENERIC_CODE(MachineName)              \
  std::string MachineName::machine_id = # MachineName;

#endif /* STATE_MACHINE_H */
/*****************************************************************************/
/*****************************************************************************/
