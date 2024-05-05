#pragma once

#include <iostream>
#include <iomanip>
#include <string>

#include <aurora-engine/Log/Internals/Internals.h>

#ifndef LOG_VERBOSITY
#define LOG_VERBOSITY 0
#endif

namespace ELogVerbosity
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

    std::string EnumToString(ELogVerbosity::Type e);
}

template <typename... Args>
inline void Log(const char *const scope, const ELogVerbosity::Type verbosity,
                const char *const message, Args... args)
{
    if (verbosity <= LOG_VERBOSITY)
    {
        switch (verbosity)
        {
        case ELogVerbosity::Fatal:
            std::cout << "\033[1;31m";
            break;
        case ELogVerbosity::Error:
            std::cout << "\033[1;31m";
            break;
        case ELogVerbosity::Warn:
            std::cout << "\033[33m";
            break;
        case ELogVerbosity::Info:
            std::cout << "\033[34m";
            break;
        default:
            break;
        }

        std::cout << "[" << ELogVerbosity::EnumToString(verbosity) << "]";

        if (scope[0] != 0)
        {
            std::cout << "[" << scope << "]";
        }

        std::cout << " ";

        ArgsPrint(message, args...);

        // Resets colors
        std::cout
            << "\033[0m";

        std::cout << std::endl;
    }
}

#define DECLARE_LOG(scope)                                          \
    template <typename... Args>                                     \
    inline void Log##scope(const ELogVerbosity::Type verbosity,     \
                           const char *const message, Args... args) \
    {                                                               \
        Log(#scope, verbosity, message, args...);                   \
    }
