#include "Vertex.h"

Vertex::Vertex(Vector3 pos, Vector3 normal, Vector2 tex)
{
    this->position = pos;
    this->normal = normal;
    this->textureCoordinates = tex;
}