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

#define COMMAND_MAX_ARG 32

typedef struct {
  int argc;
  char * argv[COMMAND_MAX_ARG];
} Command;

extern Command curr_command;

void interpret_command(char * comm, char * output);

int is_command_type(char * str);


