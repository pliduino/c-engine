#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Vertex.h"

struct ObjVertexInfo
{
    int vertex, textureCoordinate, normal;

    ObjVertexInfo(int v, int t, int n)
    {
        vertex = v;
        textureCoordinate = t;
        normal = n;
    }
};

class ObjReader
{
private:
public:
    std::vector<Vector3> positions;
    std::vector<Vector2> textureCoordinates;
    std::vector<Vector3> normals;

    std::vector<float> vertexData;

    std::vector<std::vector<ObjVertexInfo>>
        faces;

    ObjReader(/* args */);
    ~ObjReader();
    void ReadFile(const char *path);
    void Triangulate();
};