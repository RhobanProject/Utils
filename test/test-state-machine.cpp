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
#include <iostream>
using namespace std;

#include "ticks.h"
#include "state_machine.h"
#include "config_file.h"
#include "test-state-machine.h"

/*****************************************************************************/
int k;

SMTMachine the_machine;

MACHINE_GENERIC_CODE(SMTMachine);
void SMTMachine::entry() {};
void SMTMachine::activity() {};
void SMTMachine::quit() {};
State * SMTMachine::transition() { return NULL; };

/*****************************************************************************/
/* Behaviours                                                                */
/*****************************************************************************/
STATE_GENERIC_CODE(&the_machine,SMTestInit);

bool SMTestInit::terminal() { return false; };
void SMTestInit::entry()    { k = 0; };
void SMTestInit::activity() {};
void SMTestInit::quit() {};

State * SMTestInit::transition() {
	TRANSITION(1, SMTestCount);
	return NULL;
};

/*****************************************************************************/
STATE_GENERIC_CODE(&the_machine,SMTestCount);

bool SMTestCount::terminal() { return false; };
void SMTestCount::entry()    { 
  cout << "going in Count state!" << endl; cout << "First, let us sleep a bit\n"; sleep_tick(3); 
};
void SMTestCount::activity() { if (k==7) { cout << "k==7, let us sleep a bit\n"; sleep_tick(2); } k++; };
void SMTestCount::quit() { cout << "bye bye Count state." << endl; };

State * SMTestCount::transition() {
  ACTION_TRANSITION((k == 10), SMTestNext, { printf("action on transtion\n"); } );    // uses TRANSITION macro with a condition
  if (k==20) { cout << "this is the end!" << endl; JUMP(SMTheEnd); }  // or uses the jump macro without condition for more complex behaviour
  return NULL;
};

/*****************************************************************************/
STATE_GENERIC_CODE(&the_machine,SMTestNext);

bool SMTestNext::terminal() { return false; };
void SMTestNext::entry()    { 
  k = 15; 
};
void SMTestNext::activity() {};
void SMTestNext::quit() {};

State * SMTestNext::transition() {
  TRANSITION(1, SMTestCount);
  return NULL;
};

/*****************************************************************************/
STATE_GENERIC_CODE(&the_machine,SMTheEnd);

bool SMTheEnd::terminal() { return true; };
void SMTheEnd::entry()    {
};
void SMTheEnd::activity() {};
void SMTheEnd::quit() {};

State * SMTheEnd::transition() { return NULL; };

/*****************************************************************************/

int main(int argc, char * argv[]) {

	cout << "-------------------------\n";
	cout << "State Machine System Test\n";
	cout << "-------------------------\n";

	the_machine.reset();
	while (the_machine.tic()) {
		cout << k << endl;
		syst_wait_ms(200);
	}

};

/*****************************************************************************/
/*****************************************************************************/

