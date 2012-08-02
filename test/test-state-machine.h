/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
#ifndef TEST_INIT_MACHINE_H
#define TEST_INIT_MACHINE_H

#include "state_machine.h"

/*****************************************************************************/
/* Declaration of states                                                     */
/*****************************************************************************/

DECLARE_STATE(SMTestInit);
DECLARE_STATE(SMTestCount);
DECLARE_STATE(SMTestNext);
DECLARE_STATE(SMTheEnd);

DECLARE_MACHINE(SMTMachine, SMTestInit);

#endif /* TEST_INIT_MACHINE_H */
/*****************************************************************************/
/*****************************************************************************/
