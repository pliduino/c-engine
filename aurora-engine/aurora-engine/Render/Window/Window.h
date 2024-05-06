#pragma once

#include <aurora-engine/DataStructures/Events/Event.h>

enum class EKey
{
    A,
    D,
    E,
    S,
    W,
};

enum class EKeyState
{
    Pressed,
    Hold,
    Released,
};

class IWindow
{
public:
    Event<EKey, EKeyState> OnKeyPress;

protected:
    int Height, Width;
    bool isVsync = true;

public:
    virtual ~IWindow(){};

    virtual void Init() = 0;

    virtual bool ShouldClose() = 0;
    virtual void Tick() = 0;
    virtual void GetSize(int &width, int &height) = 0;
};
