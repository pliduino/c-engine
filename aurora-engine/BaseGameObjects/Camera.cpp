#include "Camera.h"

#include <aurora-engine/Objects/GameObject.h>
#include <aurora-engine/BaseComponents/Transform.h>
#include <aurora-engine/AssetManager/AssetManager.h>

#include <aurora-engine/Log/Log.h>

GCamera::GCamera()
{
    Name = "Camera";
    Near = 0.1f;
    Far = 100.0f;
    Fov = 45.0f;
    Transform = AddComponent(new CTransform());
}

GCamera::~GCamera()
{
}

void GCamera::Start()
{
}
