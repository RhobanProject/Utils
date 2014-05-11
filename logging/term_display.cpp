#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#ifndef MSVC
#include <unistd.h>
#endif
#include "term_display.h"
#include <timing/chrono.h>

Rhoban::chrono tt_chr;

bool colorsAllowed = false;


#ifdef WIN32
COORD coordScreen;
HANDLE hConsole = NULL;
#else
#endif

#ifdef _MSC_VER

#define CCALL __cdecl
#pragma section(".CRT$XCU",read)
#define INITIALIZER(f) \
	static void __cdecl f(void); \
	__declspec(allocate(".CRT$XCU")) void(__cdecl*f##_)(void) = f; \
	static void __cdecl f(void)

#elif defined(__GNUC__)

#define CCALL
#define INITIALIZER(f) \
	static void f(void) __attribute__((constructor)); \
    static void f(void)

#endif

/*
typedef struct _CONSOLE_SCREEN_BUFFER_INFO {
COORD      dwSize;
COORD      dwCursorPosition;
WORD       wAttributes;
SMALL_RECT srWindow;
COORD      dwMaximumWindowSize;
} CONSOLE_SCREEN_BUFFER_INFO;
*/

INITIALIZER(init_term_support)
{
#ifndef MSVC
  if (isatty(STDOUT_FILENO)){
    // TODO terminal capability should be checked before allowing colors
    // source: http://stackoverflow.com/a/2616912/2104361
    colorsAllowed = true;
  }
#else
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	colorsAllowed = true;
#endif
}
/*
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
#define TC_BLANC         "97
*/

/*	FOREGROUND_BLUE	Text color contains blue.
FOREGROUND_GREEN	Text color contains green.
FOREGROUND_RED	Text color contains red.
FOREGROUND_INTENSITY*/

int term_color_enabled = 1;

void term_enable_colors() {
  term_color_enabled = 1;
}

void term_disable_colors() {
  term_color_enabled = 0;
}

void term_set_color(const char * c, char * out){
	if (colorsAllowed && term_color_enabled){
#ifndef WIN32
    if (out == NULL)
      printf("\033[%sm", c);
    else
      sprintf(out, "\033[%sm", c);
#else
		std::string color(c);
		WORD code;
		if (color == TC_BLACK || color == TC_WHITE || color == TC_BLANC)
			code = FOREGROUND_INTENSITY;
		else if (color == TC_RED)
			code = FOREGROUND_RED | FOREGROUND_INTENSITY;
		else if (color == TC_GREEN)
			code = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		else if (color == TC_YELLOW)
			code = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		else if (color == TC_BLUE)
			code = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		else if (color == TC_MAGENTA)
			code = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;
		else
			code = FOREGROUND_RED;


		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		FillConsoleOutputAttribute(hConsole, code, csbi.dwSize.X * csbi.dwSize.Y, coordScreen, NULL);
#endif
	}
}

void term_separator(char * out) {
  if (out == NULL)
    printf("-------------------------------------------------------------------------------\n");
  else
    sprintf(out, "-------------------------------------------------------------------------------\n");
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
