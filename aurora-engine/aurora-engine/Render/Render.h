#pragma once

#include <string>

#include <glm/glm.hpp>

#include <aurora-engine/Render/Material.h>

class Scene;
class CModelRenderer;
class CTransform;

typedef unsigned int GLuint;

class GGameObject;
class Scene;
class GCamera;
class CTransform;
struct GLFWwindow;

class Render
{
private:
    GLFWwindow *window;
    double fps;
    double mspf;

    GLuint vbo, depthMapFBO, depthMap,
        vertex_array;

    bool showFps, bindMouse = true;

    inline void GenBuffers();
    inline void Init();
    inline void Draw(GCamera *camera, CTransform *transform);
    inline void RenderObject(CModelRenderer *modelRenderer, glm::mat4 view, glm::mat4 projection);

    // Will be removed later with proper UI implementations
    inline void ImGUI(CTransform *&transformToMove);

public:
    Render(/* args */);
    ~Render();
    void render(Scene *scene);

    Render *ShowFps();
    Render *HideFps();
    Scene *scene;
};