/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
#ifndef UTILS_LOG_H
#define UTILS_LOG_H

#include <sstream>
#include <cstdio>
#include <string>
#include <string.h>
#include <time.h>

#define LOG_LEVEL_ERROR   1
#define LOG_LEVEL_MESSAGE 2
#define LOG_LEVEL_DEBUG   3

#ifdef HAVE_COLORS
#define TEST_HAVE_COLORS 1
#else
#define TEST_HAVE_COLORS 0
#endif

#ifndef NDEBUG
#define LOG_DEBUG 1
#else
#define LOG_DEBUG 0
#endif

#define COLOR_NONE 0

#define T_COLOR_RED "\e[0;31m"
#define T_COLOR_GREEN "\e[0;32m"
#define T_COLOR_BLUE "\e[0;34m"
#define T_COLOR_RESET "\e[0m"

#define LOG_CPP(level, loglevel, component, message) \
		{ \
	if (level <= loglevel) { \
                ostringstream oss__; \
                oss__ << message; \
		struct tm now__; \
		time_t timestamp__; \
		\
		if (TEST_HAVE_COLORS) { \
			if (level < 2) printf(T_COLOR_RED); \
			if (level > 2) printf(T_COLOR_BLUE); \
		} \
		time(&timestamp__); \
		now__ = *localtime(&timestamp__); \
		printf("[%02d:%02d:%02d] ",  \
				now__.tm_hour, now__.tm_min, now__.tm_sec); \
				\
				if (LOG_DEBUG) { \
					printf("[%s:%d] ", (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__), __LINE__); \
				} \
				\
				printf("[%s] ", component); \
				\
				printf("%s\n", oss__.str().c_str()); \
				if (TEST_HAVE_COLORS) { \
					printf(T_COLOR_RESET); \
				} \
				fflush(stdout); \
	}\
		}

#define LOG(level, loglevel, component, ...) \
		if (level <= loglevel) { \
			struct tm now__; \
			time_t timestamp__; \
			\
			if (TEST_HAVE_COLORS) { \
				if (level < 2) printf(T_COLOR_RED); \
				if (level > 2) printf(T_COLOR_BLUE); \
			} \
			time(&timestamp__); \
			now__ = *localtime(&timestamp__); \
			printf("[%02d/%02d/%04d %02d:%02d:%02d] ",  \
					now__.tm_mday, now__.tm_mon+1, now__.tm_year+100, now__.tm_hour, now__.tm_min, now__.tm_sec); \
					\
					if (LOG_DEBUG) { \
						printf("[%s:%d] ", (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__), __LINE__); \
					} \
					\
					printf("[%s] ", component); \
					\
					printf(__VA_ARGS__); \
					printf("\n"); \
					if (TEST_HAVE_COLORS) { \
						printf(T_COLOR_RESET); \
					} \
					fflush(stdout); \
		}

#endif // UTILS_LOG_H
