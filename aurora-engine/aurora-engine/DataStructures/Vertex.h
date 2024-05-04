#include <aurora-engine/DataStructures/Vector2.h>
#include <aurora-engine/DataStructures/Vector3.h>

struct Vertex
{
    Vector3 position;
    Vector2 textureCoordinates;
    Vector3 normal;

    Vertex();
    Vertex(Vector3 pos, Vector3 normal, Vector2 tex);
};
