#pragma once

class IWindow
{
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
