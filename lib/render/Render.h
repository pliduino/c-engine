#pragma once

#include <unordered_map>
#include <string>

#include <glm/glm.hpp>

class Scene;
class ModelRenderer;

typedef unsigned int GLuint;

class GameObject;
class GLFWwindow;

class Render
{
private:
    GLFWwindow *window;
    std::unordered_map<std::string, unsigned int> programIds;

    GLuint vertex_buffer,
        vertex_array;

    bool showFps;

    inline void GenBuffers();
    inline void Init();
    void RenderObject(ModelRenderer *modelRenderer, glm::mat4 view, glm::mat4 projection);

public:
    Render(/* args */);
    ~Render();
    void render(Scene *scene);

    Render *ShowFps();
    Render *HideFps();
};