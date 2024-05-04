#pragma once

#include <aurora-engine/DataStructures/Vector3.h>

class BoundingBox
{
private:
public:
    Vector3 center;
    Vector3 bounds;
    BoundingBox(const Vector3 *vertices, const size_t vertice_count);
    BoundingBox(const float *vertices, const size_t vertice_count);
    BoundingBox();
    ~BoundingBox();
};