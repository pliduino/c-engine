#pragma once

#include <aurora-engine/Objects/GameObject.h>

class CTransform;

class GCamera : public GGameObject
{
private:
    /* data */
public:
    CTransform *Transform;
    float Fov;
    float Near;
    float Far;

    GCamera(/* args */);
    ~GCamera();

    virtual void Start() override;
};
