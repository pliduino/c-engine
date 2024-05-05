#include "WindowGLFW.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    // if (key == GLFW_KEY_A && action == GLFW_REPEAT)
    // {
    //     render->scene->mainCamera->Transform->Position.x -= 0.3;
    // }

    // if (key == GLFW_KEY_D && action == GLFW_REPEAT)
    // {
    //     render->scene->mainCamera->Transform->Position.x += 0.3;
    // }

    // if (key == GLFW_KEY_SPACE && action == GLFW_REPEAT)
    // {
    //     render->scene->mainCamera->Transform->Position.y += 0.3;
    // }

    // if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_REPEAT)
    // {
    //     render->scene->mainCamera->Transform->Position.y -= 0.3;
    // }

    // if (key == GLFW_KEY_W && action == GLFW_REPEAT)
    // {
    //     render->scene->mainCamera->Transform->Position.z += 0.3;
    // }

    // if (key == GLFW_KEY_S && action == GLFW_REPEAT)
    // {
    //     render->scene->mainCamera->Transform->Position.z -= 0.3;
    // }

    // const float rotSpeed = 0.1;

    // if (key == GLFW_KEY_Q && action == GLFW_REPEAT)
    // {
    //     render->scene->mainCamera->Transform->Rotation *= TQuaternion::FromEulerAngle(0, -rotSpeed, 0);
    // }

    // if (key == GLFW_KEY_E && action == GLFW_REPEAT)
    // {
    //     render->scene->mainCamera->Transform->Rotation *= TQuaternion::FromEulerAngle(0, +rotSpeed, 0);
    // }

    // if (key == GLFW_KEY_F && action == GLFW_REPEAT)
    // {
    //     render->scene->mainCamera->Transform->Rotation *= TQuaternion::FromEulerAngle(-rotSpeed, 0, 0);
    // }

    // if (key == GLFW_KEY_R && action == GLFW_REPEAT)
    // {
    //     render->scene->mainCamera->Transform->Rotation *= TQuaternion::FromEulerAngle(+rotSpeed, 0, 0);
    // }
}

static void ErrorCallback(int error, const char *description)
{
    LogWindowGLFW(ELogVerbosity::Error, description);
}

void TWindowGLFW::Init()
{
    LogWindowGLFW(ELogVerbosity::Info, "Opening Window");

    // Initializing GLFW
    if (!glfwInit())
    {
        LogWindowGLFW(ELogVerbosity::Error, "GLFW init error");
        return;
    }
    glfwWindowHint(GLFW_SAMPLES, 4); // MSAA Anti Aliasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Initializing Window
    window = glfwCreateWindow(1280, 720, "Aura", NULL, NULL);
    if (!window)
    {
        LogWindowGLFW(ELogVerbosity::Error, "Window creation error");
        glfwTerminate();
        return;
    }

    glfwSetErrorCallback(ErrorCallback);
    glfwSetKeyCallback(window, KeyCallback);
    glfwMakeContextCurrent(window);

    // Ties to monitor refresh rate
    if (isVsync)
    {
        glfwSwapInterval(1);
    }

    LogWindowGLFW(ELogVerbosity::Info, "Opening Window [END]");

    // TODO: MOVE OUT OF THIS LATER

    // Initializing IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    ImGui_ImplGlfw_InitForOpenGL(window, true); // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    LogWindowGLFW(ELogVerbosity::Info, "Initialized ImGui");
}

bool TWindowGLFW::ShouldClose()
{
    return glfwWindowShouldClose(this->window);
};

void TWindowGLFW::GetSize(int &width, int &height)
{
    glfwGetWindowSize(window, &width, &height);
}

void TWindowGLFW::Tick()
{
    glfwPollEvents();
    glfwSwapBuffers(window);
}

TWindowGLFW::~TWindowGLFW()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}
