#include "Camera.h"

#include <aurora-engine/Objects/GameObject.h>
#include <aurora-engine/BaseComponents/Transform.h>

GCamera::GCamera(/* args */)
{
    Name = "Camera";
    Near = 0.1f;
    Far = 100.0f;
    Fov = 45.0f;
    Transform = AddComponent(new class CTransform());
}

GCamera::~GCamera()
{
}

void GCamera::Start()
{
}
