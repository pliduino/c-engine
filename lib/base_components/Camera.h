#pragma once

#include "Component.h"
#include "Transform.h"

class Camera : public Component
{
private:
    /* data */
public:
    Transform *transform;
    float fov;
    float near;
    float far;

    Camera(/* args */);
    ~Camera();

    void Start() override;
};
