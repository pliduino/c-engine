#pragma once

#include <aurora-engine/Containers/Array.h>

#include <aurora-engine/DataStructures/Events/Function.h>

template <typename... Args>
class Event
{
private:
    TArray<TFunction<void(Args...)>> Functions;

public:
    Event(){};
    ~Event(){};

    void Invoke(Args... args)
    {
        for (TFunction function : Functions)
        {
            function(args...);
        }
    };

    void Subscribe(TFunction<void(Args...)> function)
    {
        Functions.Add(function);
    };
};
