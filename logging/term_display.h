#ifndef TERM_DISPLAY_H
#define TERM_DISPLAY_H

#define TERM_CLEAR printf ("%c[H%c[J",27,27)
#define TERM_CLEAR_LINE printf ("%c[J",27)
#define TERM_CURSOR_HOME printf ("%c[H",27)
#define TERM_CURSOR_LEFT(x) printf("\033[%dD", x);
#define TERM_CURSOR_RIGHT(x) printf("\033[%dC", x);
#define TERM_CURSOR_GOTO(x,y) printf ("%c[%d;%dH",27,(y),(x))
#define TERM_CURSOR_SAVE printf ("%c7",27)
#define TERM_CURSOR_RESTORE printf ("%c8",27)
#define TERM_CURSOR_UP printf ("%cA",27)
#define TERM_FONT_BOLD printf("%c[1m",27)
#define TERM_FONT_NORMAL printf("%c[m",27) 

#define TC_DEFAULT "0"
#define TC_HIGHLIGHT "1"
#define TC_BLINK "5"
#define TC_INVERSE "7"

/* Color codes have been updated according to :
 * - http://misc.flogisoft.com/bash/tip_colors_and_formatting
 * and
 * - http://en.wikipedia.org/wiki/ANSI_escape_code#Colors
 */
#define TC_BLACK         "30"
#define TC_RED           "31"
#define TC_GREEN         "32"
#define TC_YELLOW        "33"
#define TC_BLUE          "34"
#define TC_MAGENTA       "35"
#define TC_CYAN          "36"
#define TC_LIGHT_GRAY    "37"
#define TC_DARK_GRAY     "90"
#define TC_LIGHT_RED     "91"
#define TC_LIGHT_GREEN   "92"
#define TC_LIGHT_YELLOW  "93"
#define TC_LIGHT_BLUE    "94"
#define TC_LIGHT_MAGENTA "95"
#define TC_LIGHT_CYAN    "96"
#define TC_WHITE         "97"
#define TC_BLANC         "97"// Kept for compatibility, deprecated (french name)
#define TERM_COLOR(c) {term_set_color(c);}

void term_set_color(const char * c);
void term_separator();
void print_n_times(int n, char c);
void term_title(char * title);
void term_subtitle(char * title);

#endif /* TERM_DISPLAY_H */


