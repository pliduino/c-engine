#pragma once

#include <iostream>
#include <aurora-engine/Log/Log.h>

// TODO: Add stack trace to CRASH_MESSAGE

#define CRASH_MESSAGE(fmt, ...)                          \
    do                                                   \
    {                                                    \
        Log("", ELogVerbosity::Fatal, fmt, __VA_ARGS__); \
        abort();                                         \
    } while (0)

#ifdef ASSERT

#define check(assert, fmt, ...)                                                                                         \
    do                                                                                                                  \
    {                                                                                                                   \
        if (!(assert))                                                                                                  \
        {                                                                                                               \
            CRASH_MESSAGE("Assertion failed: " #assert " == false ({}:{})\n\t" fmt, __FILE__, __LINE__, ##__VA_ARGS__); \
        }                                                                                                               \
    } while (0)

#define verify(assert, fmt, ...)                                                                                        \
    do                                                                                                                  \
    {                                                                                                                   \
        if (!(assert))                                                                                                  \
        {                                                                                                               \
            CRASH_MESSAGE("Assertion failed: " #assert " == false ({}:{})\n\t" fmt, __FILE__, __LINE__, ##__VA_ARGS__); \
        }                                                                                                               \
    } while (0)

#else
#define check(assert, fmt, ...) (void)0
#define verify(assert, fmt, ...) \
    do                           \
    {                            \
        assert                   \
    } while (0)
#endif