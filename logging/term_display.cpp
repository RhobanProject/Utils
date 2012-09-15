#include <stdio.h>
#include <stdlib.h>
#include "term_display.h"

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
