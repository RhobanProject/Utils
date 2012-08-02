/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
/*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#include "TimedThread.hpp"
#include "ticks.h"
#include "TickMachine.hpp"

#define OUTPUT(msg...) printf(msg); fflush(stdout);

int n = 0;

class MyThread : public TimedThread {
  void step() {
    OUTPUT("inside the thread step %d\n", n++); 
  };
};

int main(int argc, char * argv[]) {

  //  TickMachine::init_tick_machine();

  MyThread my_thread;
  my_thread.init(10.0, true);
  OUTPUT("Started !\n");
  syst_wait_ms(2000);
  
  my_thread.kill();
} 

// TODO est-ce qu'un thread peut dire qu'il est mort:
// par exemple step pourrait retourner un booleen

// Est-ce que ticks.h est toujours utilisé ?

/*****************************************************************************/
