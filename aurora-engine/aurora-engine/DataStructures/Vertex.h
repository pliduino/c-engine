#include <aurora-engine/DataStructures/Vector2.h>
#include <aurora-engine/DataStructures/Vector3.h>

struct TVertex
{
    TVector3 Position;
    TVector2 TextureCoordinates;
    TVector3 Normal;

    TVertex();
    TVertex(TVector3 pos, TVector3 normal, TVector2 tex);
};
