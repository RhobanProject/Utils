/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
/** ***************************************************************************
 *  \file    state_machine.cpp
 *  \author  Hugo Gimbert - Olivier Ly
 *  \date    2010-12
 *
 *  \brief   State machine infrastructure.
 *****************************************************************************/
#include "state_machine.h"
#include <list>
#include <string>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

/*****************************************************************************/
#define DBUG(msg,...) { printf(msg __VA_ARGS__); fflush(stdout); };
/*****************************************************************************/

int StateMachine::reset() {
  init();
  if (init_state == NULL) return 0;
  active_state = init_state;
  if (debug) printf("[Machine %s]: starting from state %s.\n", get_machine_id().c_str(), init_state->get_state_id().c_str());
  this->entry();
  init_state->entry();
  return 1;
}

int StateMachine::tic() {
  
  if (next_state != NULL) {
    if (transition_delay > 0) {
      transition_delay--;
    }
    else {
      if (debug) printf("[Machine %s]: leaving %s\n", get_machine_id().c_str(), active_state->get_state_id().c_str());
      active_state->quit();
      active_state->intern_set_active(false);
      active_state = next_state;
      active_state->father = this; 
      next_state = NULL;
      active_state->intern_set_active(true);
      if (debug) printf("[Machine %s]: entering %s\n", get_machine_id().c_str(), active_state->get_state_id().c_str());
      active_state->entry();
    }
  }
  
  if (active_state==NULL) return -1;

  if (!(active_state->is_sys_wait_msing())) {
    active_state->activity();
    this->activity();
  } 

  /* look for transition */
  if (next_state != NULL) return 1;
  State * new_state = NULL;
  new_state = this->transition(); // First: check for machine global transition
  if (new_state == NULL) new_state = active_state->transition(); // Then: one checks the transition of the current state
  if (new_state != NULL)
    next_state = new_state;

  if (active_state->terminal()) { 
    this->quit();
    return 0;
  }
  else return 1;
}

StateMachine::StateMachine() : 
  debug(false),
  transition_delay(0),
  init_state(NULL), 
  active_state(NULL), 
  next_state(NULL),
  frequency(TICK_FREQUENCY_DEFAULT)
{}


 
/*****************************************************************************/
/*****************************************************************************/
