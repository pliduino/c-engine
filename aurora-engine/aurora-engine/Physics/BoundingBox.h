#pragma once

#include <aurora-engine/DataStructures/Vector3.h>

class BoundingBox
{
private:
public:
    TVector3 center;
    TVector3 bounds;
    BoundingBox(const TVector3 *vertices, const size_t vertice_count);
    BoundingBox(const float *vertices, const size_t vertice_count);
    BoundingBox();
    ~BoundingBox();
};