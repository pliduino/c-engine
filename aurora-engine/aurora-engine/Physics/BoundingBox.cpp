
#include "BoundingBox.h"

BoundingBox::BoundingBox()
{
}

BoundingBox::BoundingBox(const TVector3 *vertices, const size_t vertice_count)
{
    TVector3 minCoords = TVector3(vertices[0]);
    TVector3 maxCoords = TVector3(vertices[0]);

    for (size_t i = 1; i < vertice_count; i++)
    {
        minCoords.x = vertices[i].x < minCoords.x ? vertices[i].x : minCoords.x;
        minCoords.y = vertices[i].y < minCoords.y ? vertices[i].y : minCoords.y;
        minCoords.z = vertices[i].z < minCoords.z ? vertices[i].z : minCoords.z;

        maxCoords.x = vertices[i].x > maxCoords.x ? vertices[i].x : maxCoords.x;
        maxCoords.y = vertices[i].y > maxCoords.y ? vertices[i].y : maxCoords.y;
        maxCoords.z = vertices[i].z > maxCoords.z ? vertices[i].z : maxCoords.z;
    }

    center = (maxCoords + minCoords) / 2;
    bounds = (maxCoords - minCoords) / 2;
}

BoundingBox::BoundingBox(const float *vertices, const size_t vertice_count)
{
    TVector3 minCoords = TVector3(vertices[0], vertices[1], vertices[2]);
    TVector3 maxCoords = TVector3(vertices[0], vertices[1], vertices[2]);

    for (size_t i = 1; i < vertice_count; i++)
    {
        minCoords.x = vertices[(i * 3)] < minCoords.x ? vertices[(i * 3)] : minCoords.x;
        minCoords.y = vertices[(i * 3) + 1] < minCoords.y ? vertices[(i * 3) + 1] : minCoords.y;
        minCoords.z = vertices[(i * 3) + 2] < minCoords.z ? vertices[(i * 3) + 2] : minCoords.z;

        maxCoords.x = vertices[(i * 3)] > maxCoords.x ? vertices[(i * 3)] : maxCoords.x;
        maxCoords.y = vertices[(i * 3) + 1] > maxCoords.y ? vertices[(i * 3) + 1] : maxCoords.y;
        maxCoords.z = vertices[(i * 3) + 2] > maxCoords.z ? vertices[(i * 3) + 2] : maxCoords.z;
    }

    center = (maxCoords + minCoords) / 2;
    bounds = (maxCoords - minCoords) / 2;
}

BoundingBox::~BoundingBox()
{
}