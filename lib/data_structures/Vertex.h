#include "Vector2.h"
#include "Vector3.h"

struct Vertex
{
    Vector3 position;
    Vector2 textureCoordinates;
    Vector3 normal;

    Vertex();
    Vertex(Vector3 pos, Vector3 normal, Vector2 tex);
};
