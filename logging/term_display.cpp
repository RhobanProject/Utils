#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "term_display.h"
#include "chrono.h"

chrono tt_chr;

void term_separator() {
  printf("-------------------------------------------------------------------------------\n");
}

void print_n_times(int n, char c) {
  char str[1024];
  int k;
  for (k=0; k<n; k++) str[k] = c;
  str[k] = 0;
  printf("%s",str);
}

void term_subtitle(char * title) {
  printf("-- %s --\n", title);
}

void term_title(char * title) {
  char str[512];
  sprintf(str, "- %s -\n", title);
  printf("%s", str);
  print_n_times(strlen(str), '-');
  printf("\n");
}
