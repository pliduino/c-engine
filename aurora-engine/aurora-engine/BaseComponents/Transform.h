#pragma once

#include <iostream>

#include <aurora-engine/Objects/Component.h>
#include <aurora-engine/DataStructures/Vector3.h>
#include <aurora-engine/DataStructures/Quaternion.h>

class Transform : public CComponent
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