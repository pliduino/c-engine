#pragma once

#include <iostream>
#include <sstream>
#include <string>

inline void ArgsPrintInternal(std::stringstream stream)
{
    char tmp;
    while ((tmp = stream.get()), stream)
    {
        if (tmp == '{')
        {
            tmp = stream.get();
            if (tmp == '}')
            {
                ArgsPrintInternal(std::move(stream));
                break;
            }

            // If not paired print missed token and continue
            std::cout << '{';
        }
        std::cout << tmp;
    }
}

template <typename T, typename... Args>
void ArgsPrintInternal(std::stringstream stream, T unpackedArg, Args... args)
{
    char tmp;

    std::cout << unpackedArg;

    while ((tmp = stream.get()), stream)
    {
        if (tmp == '{')
        {
            tmp = stream.get();
            if (tmp == '}')
            {
                ArgsPrintInternal(std::move(stream), args...);
                break;
            }

            // If not paired print missed token and continue
            std::cout << '{';
        }
        std::cout << tmp;
    }
}

template <typename... Args>
void ArgsPrint(const char *const formatString, Args... args)
{
    std::stringstream stream(formatString);
    char tmp;

    while ((tmp = stream.get()), stream)
    {
        if (tmp == '{')
        {
            tmp = stream.get();
            if (tmp == '}')
            {
                ArgsPrintInternal(std::move(stream), args...);
                break;
            }

            // If not paired print missed token and continue
            std::cout << '{';
        }
        std::cout << tmp;
    }
}
