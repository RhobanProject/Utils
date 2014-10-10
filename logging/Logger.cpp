#include <cstdio>
#include <cstdarg>
#ifndef WIN32
#include <unistd.h>
#endif
#include "Logger.h"

#define T_COLOR_RED     "\x1b[0;31m"
#define T_COLOR_GREEN   "\x1b[0;32m"
#define T_COLOR_YELLOW  "\x1b[0;33m"
#define T_COLOR_BLUE    "\x1b[0;34m"
#define T_COLOR_RESET   "\x1b[0m"

namespace Rhoban
{
    Logger::Logger(std::string module_, LoggerLevel level_)
        : module(module_),
        level(level_)
    {
#ifdef WIN32
        colors = true;
#else
        colors = isatty(STDERR_FILENO);
#endif
    }

    void Logger::prefix(LoggerLevel lvl)
    {
        struct tm now;
        time_t timestamp;
        time(&timestamp);
        now = *localtime(&timestamp);

        fprintf(stderr, "[%02d:%02d:%02d] ", now.tm_hour, now.tm_min, now.tm_sec);
        fprintf(stderr, "[%s] ", module.c_str());
    }

    void Logger::colorize(LoggerLevel lvl)
    {
        if (colors) {
            const char *color = NULL;
            switch (lvl) {
                case LoggerError:
                    color = T_COLOR_RED;
                    break;
                case LoggerWarning:
                    color = T_COLOR_YELLOW;
                    break;
                case LoggerMessage:
                    color = T_COLOR_RESET;
                    break;
                case LoggerSuccess:
                    color = T_COLOR_GREEN;
                    break;
                case LoggerDebug:
                    color = T_COLOR_BLUE;
                    break;
            }

            if (color != NULL) {
                fprintf(stderr, "%s", color);
            }
        }
    }

    void Logger::resetColor()
    {
        if (colors) {
            fprintf(stderr, "%s", T_COLOR_RESET);
        }
    }

#define LOG(lvl)                        \
    if (lvl <= level) {                  \
        colorize(lvl);                  \
        prefix(lvl);                    \
        va_list args;                   \
        va_start(args, fmt);            \
        vfprintf(stderr, fmt, args);    \
        va_end(args);                   \
        fprintf(stderr, "\n");          \
        resetColor();                   \
    }

    void Logger::error(const char *fmt, ...)
    {
        LOG(LoggerError);
    }
    
    void Logger::warning(const char *fmt, ...)
    {
        LOG(LoggerWarning);
    }
    
    void Logger::log(const char *fmt, ...)
    {
        LOG(LoggerMessage);
    }
    
    void Logger::success(const char *fmt, ...)
    {
        LOG(LoggerSuccess);
    }
    
    void Logger::debug(const char *fmt, ...)
    {
        LOG(LoggerDebug);
    }
}
