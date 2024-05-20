#include "Vertex.h"

TVertex::TVertex()
{
}

TVertex::TVertex(TVector3 pos, TVector3 normal, TVector2 tex)
{
    this->Position = pos;
    this->Normal = normal;
    this->TextureCoordinates = tex;
}
