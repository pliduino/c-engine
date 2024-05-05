#pragma once

#include <iostream>
#include <aurora-engine/Log/Log.h>

// TODO: Add stack trace to CRASH_MESSAGE

#define CRASH_MESSAGE(fmt, ...)                      \
    Log("", ELogVerbosity::Fatal, fmt, __VA_ARGS__); \
    abort();                                         \
    (void)0

#ifdef ASSERT
#define check(assert, fmt, ...)                                                                                   \
    if (!(assert))                                                                                                \
    {                                                                                                             \
        CRASH_MESSAGE("Assertion failed: " #assert " == false ({}:{})\n\t" fmt, __FILE__, __LINE__, __VA_ARGS__); \
    }                                                                                                             \
    (void)0

#define verify(assert, fmt, ...)                                                                                  \
    if (!(assert))                                                                                                \
    {                                                                                                             \
        CRASH_MESSAGE("Assertion failed: " #assert " == false ({}:{})\n\t" fmt, __FILE__, __LINE__, __VA_ARGS__); \
    }                                                                                                             \
    (void)0

#else
#define check(assert, fmt, ...) (void)0
#define verify(assert, fmt, ...) \
    if (assert)                  \
    {                            \
    }
#endif