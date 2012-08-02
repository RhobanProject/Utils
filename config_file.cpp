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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config_file.h"
/****************************************************************************/
FILE * fd;

int verbose = 0;
void config_file_verbose() { verbose = 1; }
void config_file_silent() { verbose = 0; }

#define is_space(x) (x==' ' || x=='\t')

char line_buffer[256];
int lb_idx;
char lexem_buffer[256];

/* return the length of the line, or -1 if there is a eof. */
int read_line() {
	int idx = 0;
	int c;
	while ( idx < 255 && ((c = fgetc(fd)) != EOF) && (c != '\n') )
		line_buffer[idx++] = c;
	line_buffer[idx]=0;
	if (c == EOF) return -1;
	else return idx;
}

void eat_spaces(int lb_idx_max) {
	while (is_space(line_buffer[lb_idx]) && (lb_idx <= lb_idx_max)) lb_idx++;
}

void eat_lexem(int lb_idx_max) {
	eat_spaces(lb_idx_max);
	sscanf(line_buffer+lb_idx, "%s", lexem_buffer);
	lb_idx += strlen(lexem_buffer);
}

#define SYNTAX_ERROR(reason) { printf("config file syntax error: %s\n", reason); fclose(fd); return 2; }

/* return 1 if the char has been found, (caution) 2 otherwise */
int eat_char(char c, int lb_idx_max) {
	eat_spaces(lb_idx_max);
	if (line_buffer[lb_idx++] != c) { SYNTAX_ERROR("char unexpected"); }
	return 1;
}

int get_value(char * file, char * id) {

	if ((fd = fopen(file, "r")) == NULL) {
		printf("get_int_value: unable to open file %s\n", file);
		return 1;
	}

	int length;
	int found = 0;
	int print_it = 0;
	while (!found && (length = read_line()) != -1) {
		lb_idx=0;
		eat_spaces(length-1);
		if ((length-lb_idx) == 0) continue;
		if (line_buffer[lb_idx] == '#') { continue; }

		eat_lexem(length-1);
		if (strcmp(id, lexem_buffer) == 0) { found = 1; print_it = 1; }
		if (verbose && print_it == 1) printf("%s = ", lexem_buffer);
		eat_char('=', length-1);
		eat_lexem(length-1);
		if (verbose && print_it == 1) { printf("%s\n", lexem_buffer); print_it = 0; }
	}
	fclose(fd);
	if (found) return 0;
	else return -1;
}

int get_int_value(char * file, char * id, int * value) {
	int ret = get_value(file, id);
	if (ret == 0) {
		*value = atoi(lexem_buffer);
		return 0;
	} else {
		printf("%s = %d [Default value]\n", id, *value);
		return ret;
	}
}

int get_double_value(char * file, char * id, double * value) {
	int ret = get_value(file, id);
	if (ret == 0) {
		*value = atof(lexem_buffer);
		return 0;
	} else {
		printf("%s = %f [Default value]\n", id, *value);
		return ret;
	}
}

/****************************************************************************/
/****************************************************************************/


