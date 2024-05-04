#pragma once

#include <aurora-engine/Objects/Component.h>

class Transform;

class Camera : public CComponent
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
