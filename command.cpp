/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_mngt.h"
#include "command.h"
#include "control_low_level.h"
#include "util.h"
#include "ticks.h"

Command curr_command;

/*****************************************************************************/

void parse_command(char *str) {
  int idx = 0;
  int wait_for_word = 1;

  curr_command.argc = 0;

  while (str[idx] != 0) {
    
    if (str[idx] == ' '   ||
	str[idx] == '\t'  ||
	str[idx] == '\n') {
      str[idx] = 0;
      wait_for_word = 1;
    }
    else {
      if (wait_for_word) {
	curr_command.argv[curr_command.argc++] = str+idx;
	wait_for_word = 0;
      }
    }
    idx++;
  }
}

/*****************************************************************************/

int is_command_type(char * str) {
  if (curr_command.argc == 0) return 0;
  return strcmp(str, curr_command.argv[0])==0;
}

/*****************************************************************************/

#define check_parameter(n)			              \
  if (curr_command.argc != (n+1))                             \
    { fprintf(stdout, "bad number of parameter"); return; }   

/*****************************************************************************/



/*****************************************************************************/
/*****************************************************************************/
