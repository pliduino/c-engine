#pragma once

#include <unordered_map>
#include <string>

// TODO: fix this include
#include <D:/Github/c-engine/external/glm/glm/glm.hpp>

class Scene;
class ModelRenderer;
class Transform;

typedef unsigned int GLuint;

class GameObject;
struct GLFWwindow;
class Scene;
class Camera;

class Render
{
private:
    GLFWwindow *window;
    std::unordered_map<std::string, unsigned int> programIds;
    double fps;
    double mspf;

    GLuint vbo, depthMapFBO, depthMap,
        vertex_array;

    Scene *scene;

    bool showFps;

    inline void GenBuffers();
    inline void Init();
    inline void Draw(Camera *camera, Transform *transform);
    inline void RenderObject(ModelRenderer *modelRenderer, glm::mat4 view, glm::mat4 projection);

public:
    Render(/* args */);
    ~Render();
    void render(Scene *scene);

    Render *ShowFps();
    Render *HideFps();
};