#pragma once

#include <iostream>

#include <aurora-engine/Objects/Component.h>
#include <aurora-engine/DataStructures/Vector3.h>
#include <aurora-engine/DataStructures/Quaternion.h>

class CTransform : public CComponent
{
private:
    /* data */
public:
    TVector3 Position;
    TVector3 Scale;
    TQuaternion Rotation;

    CTransform(/* args */);
    ~CTransform();

    void Start() override;
    void Update() override;

    friend std::ostream &operator<<(std::ostream &os, const CTransform &t);
};