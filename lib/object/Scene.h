#pragma once

#include <vector>

#include "Camera.h"

class GameObject;

class Scene
{
private:
    /* data */
public:
    Camera *mainCamera;
    std::vector<GameObject *> objects;

    Scene(/* args */);
    ~Scene();

    void Start();
    void Update();
};
