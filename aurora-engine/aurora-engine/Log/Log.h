#pragma once

#include <iostream>
#include <iomanip>
#include <string>

#include <aurora-engine/Log/Internals/Internals.h>

#ifndef LOG_VERBOSITY
#define LOG_VERBOSITY 0
#endif

// TODO: Move this to a proper file
namespace EAnsiColor
{
    constexpr char Black[] = "\033[30m";
    constexpr char BoldRed[] = "\033[1;31m";
    constexpr char Yellow[] = "\033[33m";
    constexpr char Blue[] = "\033[34m";
}

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
        // TODO: Introduce consts for these colors
        switch (verbosity)
        {
        case ELogVerbosity::Fatal:
            std::cout << EAnsiColor::BoldRed;
            break;
        case ELogVerbosity::Error:
            std::cout << EAnsiColor::BoldRed;
            break;
        case ELogVerbosity::Warn:
            std::cout << EAnsiColor::Yellow;
            break;
        case ELogVerbosity::Info:
            std::cout << EAnsiColor::Blue;
            break;
        case ELogVerbosity::Debug:
            std::cout << EAnsiColor::Black;
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
