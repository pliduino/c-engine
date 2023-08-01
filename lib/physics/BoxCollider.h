#pragma once

#include "Component.h"
#include "BoundingBox.h"

class Transform;
class Vector3;

class BoxCollider : public Component
{
private:
    Transform *transform;
    BoundingBox boundingBox;

public:
    BoxCollider(/* args */);
    ~BoxCollider();

    inline bool IsPointInside(const Vector3 point);
    inline bool Intersect(const BoxCollider other);

    void Start() override;
    void Update() override;
};