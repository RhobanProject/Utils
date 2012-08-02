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
 *  \file    config_file.h
 *  \author  Hugo Gimbert - Olivier Ly
 *  \date    2011-01
 *
 *  \brief Ligh config file management.
 * The syntax of a config file is simple.
 * Each line is
 * - either a definition of form IDENT = value where value is a numerical value, int or double
 * - or a comment, introduced by a '#' character.
 *****************************************************************************/
#ifndef CONFIG_FILE_H
#define CONFIG_FILE_H

/*! \note
 *  each function of the form get_*_value(file,id,value) opens the file, look for
 *  the identifier id and put the corresponding value into value.
 *
 *  it returns:
 *  0 if everything is ok
 *  1 if the file could not be openned
 *  2 if the id does not exists in the file. */

int get_int_value(char * file, char * id, int * value);
int get_double_value(char * file, char * id, double * value);

/*! \brief print all the parameter's values */
void config_file_verbose();

/*! \brief does not print anything */
void config_file_silent();

#endif /* CONFIG_FILE_H */
/****************************************************************************/
/****************************************************************************/
