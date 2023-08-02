#pragma once

#include <iostream>

#include "Component.h"
#include "Vector3.h"
#include "Quaternion.h"

class Transform : public Component
{
private:
    /* data */
public:
    Vector3 position;
    Vector3 scale;
    Quaternion rotation;

    Transform(/* args */);
    ~Transform();

    void Start() override;
    void Update() override;

    friend std::ostream &operator<<(std::ostream &os, const Transform &t);
};