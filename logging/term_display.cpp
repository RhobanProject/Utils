#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "term_display.h"
#include "chrono.h"

chrono tt_chr;

bool colorsAllowed = false;

void init_term_support() __attribute__ ((constructor));

void init_term_support(){
  if (isatty(STDOUT_FILENO)){
    // TODO terminal capability should be checked before allowing colors
    // source: http://stackoverflow.com/a/2616912/2104361
    colorsAllowed = true;
  }
}

void term_set_color(const char * c){
  if (colorsAllowed){
    printf("\033[%sm", c);
  }
}

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
