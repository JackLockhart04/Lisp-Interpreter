#include "logger.h"

Logger::LogLevel Logger::logLevel = Logger::INFO;

void Logger::log(std::string message, LogLevel priority){
    // Skip when priority is too low
    if(priority < logLevel) return;

    // Print
    switch (priority){
        case Logger::DEBUG:
            std::cout << "DEBUG: " << message << std::endl;
            break;
        case Logger::INFO:
            std::cout << "INFO: " << message << std::endl;
            break;
        case Logger::WARNING:
            std::cout << "WARNING: " << message << std::endl;
            break;
        case Logger::ERROR:
            std::cout << "ERROR: " << message << std::endl;
            break;
        case Logger::CRITICAL:
            std::cout << "CRITICAL: " << message << std::endl;
            break;
        case Logger::NONE:
            break;
        default:
            std::cout << "CRITICAL: logger is messed up" << std::endl;
    }
}

void Logger::setLogLevel(LogLevel level){
    logLevel = level;
}