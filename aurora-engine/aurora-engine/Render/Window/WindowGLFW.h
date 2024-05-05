#pragma once

#include <aurora-engine/Render/Window/Window.h>
#include <aurora-engine/Pointers/Pointers.h>
#include <aurora-engine/Log/Log.h>

struct GLFWwindow;

DECLARE_LOG(WindowGLFW)

class TWindowGLFW : public IWindow
{
private:
    Owner<GLFWwindow> window;

public:
    ~TWindowGLFW();

    // IWindow Implementation
    virtual void Init() override;
    virtual bool ShouldClose() override;
    virtual void Tick() override;
    virtual void GetSize(int &width, int &height) override;
};