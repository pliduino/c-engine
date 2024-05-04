#pragma once

#include <vector>
#include <aurora-engine/Pointers/Pointers.h>

class Camera;
class GCamera;

class GGameObject;

class Scene
{
private:
    /* data */
public:
    Borrow<GCamera> mainCamera;
    std::vector<Owner<GGameObject>> objects;

    Scene(/* args */);
    ~Scene();

    void Start();
    void Update();
};
