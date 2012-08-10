#ifndef UTILS_LOG_H
#define UTILS_LOG_H

#include <string.h>
#include <stdio.h>
#include <time.h>

#ifdef NDEBUG
#define LOG_DEBUG 1
#else
#define LOG_DEBUG 0
#endif

#define LOG(condition, component, ...) \
    if (condition) { \
        printf("[%s]", component); \
        if (LOG_DEBUG) { \
        printf("[%s:%d]", (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__), __LINE__); \
        } \
        \
        struct tm now__; \
        time_t timestamp__; \
        \
        time(&timestamp__); \
        now__ = *localtime(&timestamp__); \
        printf(" [%02d/%02d/%04d %02d:%02d:%02d] ",  \
                now__.tm_mday, now__.tm_mon+1, now__.tm_year+100, now__.tm_hour, now__.tm_min, now__.tm_sec); \
        \
        printf(__VA_ARGS__); \
        printf("\n"); \
        fflush(stdout); \
    }

#endif // UTILS_LOG_H
