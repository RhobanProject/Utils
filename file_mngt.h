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

#include <string>
#include "util.h"

int store_in_file(char * name, ui8 * src, int size);

int read_file(char * name, ui8 * dest, int size);

string file_to_string(string path);

void file_put_contents(string path, string contents);

string file_get_contents(string path);

bool file_exists(string path);

#endif /* FILE_MNGT_H */

