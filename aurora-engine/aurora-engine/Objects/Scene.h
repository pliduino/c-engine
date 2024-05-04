#pragma once

#include <vector>
#include <aurora-engine/Pointers/Pointers.h>

class Camera;

class GameObject;

class Scene
{
private:
    /* data */
public:
    Borrow<Camera> mainCamera;
    std::vector<Owner<GameObject>> objects;

    Scene(/* args */);
    ~Scene();

    void Start();
    void Update();
};
