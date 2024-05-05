#pragma once

#include <iostream>
#include <iomanip>
#include <string>

#include <aurora-engine/Log/Internals/Internals.h>

#ifndef LOG_VERBOSITY
#define LOG_VERBOSITY 0
#endif

namespace LogVerbosity
{
    enum Type
    {
        Off = 0,
        Fatal = 1,
        Error = 2,
        Warn = 3,
        Info = 4,
        Debug = 5,
    };
}

template <typename... Args>
inline void Log(const char *const scope, const LogVerbosity::Type verbosity,
                const char *const message, Args... args)
{
    if (verbosity <= LOG_VERBOSITY)
    {
        switch (verbosity)
        {
        case LogVerbosity::Fatal:
            std::cout << "\033[31;42m";
            break;
        case LogVerbosity::Error:
            std::cout << "\033[1;31m";
            break;
        case LogVerbosity::Warn:
            std::cout << "\033[33m";
            break;
        case LogVerbosity::Info:
            std::cout << "\033[34m";
            break;
        default:
            break;
        }

        std::cout << std::setw(12) << std::left << scope << " | ";

        ArgsPrint(message, args...);

        // Resets colors
        std::cout
            << "\033[0m";

        std::cout << std::endl;
    }
}

#define DECLARE_LOG(scope)                                          \
    template <typename... Args>                                     \
    inline void Log##scope(const LogVerbosity::Type verbosity,      \
                           const char *const message, Args... args) \
    {                                                               \
        Log(#scope, verbosity, message, args...);                   \
    }