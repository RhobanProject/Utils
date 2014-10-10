#ifndef _RHOBAN_LOGGER_H
#define _RHOBAN_LOGGER_H

#include <string>

typedef enum {
    LoggerNone,
    LoggerError,
    LoggerWarning,
    LoggerMessage,
    LoggerSuccess,
    LoggerDebug
} LoggerLevel;

namespace Rhoban
{
    class Logger
    {
        public:
            Logger(std::string module, LoggerLevel level=LoggerSuccess);

            void colorize(LoggerLevel lvl);
            void resetColor();
            void prefix();

            void error(const char *fmt, ...);
            void warning(const char *fmt, ...);
            void log(const char *fmt, ...);
            void success(const char *fmt, ...);
            void debug(const char *fmt, ...);

            bool colors;

        protected:
            std::string module;
            LoggerLevel level;
    };
}

#endif
