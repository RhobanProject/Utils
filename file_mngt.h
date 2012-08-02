/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/

#ifndef FILE_MNGT_H
#define FILE_MNGT_H

#include "util.h"

int store_in_file(char * name, ui8 * src, int size);

int read_file(char * name, ui8 * dest, int size);


#endif /* FILE_MNGT_H */

