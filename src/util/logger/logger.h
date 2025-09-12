/*
    Logs anything below specified log level from level 0 - 5
    Ex: At log level 0 print everything, at level 4 print only critical, at 5 print nothing
*/

#pragma once

#include <string>
#include <iostream>

class Logger {
public:
    enum LogLevel {
        DEBUG = 0,
        INFO = 1,
        WARNING = 2,
        ERROR = 3,
        CRITICAL = 4,
        NONE = 5
    };

    static void log(std::string message, LogLevel priority = DEBUG);
    static void setLogLevel(LogLevel level);
private:
    // Private init so only gets called once
    static void init();

    static LogLevel logLevel;
};