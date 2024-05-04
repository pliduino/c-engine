#pragma once

template <typename T>
class TFunction
{
    T *(FunctionPointer) = nullptr;

public:
    TFunction(){};
    TFunction(T R) : FunctionPointer{R} {}

    template <typename... Args>
    auto operator()(Args... args)
    {
        return FunctionPointer(args...);
    }
};