#include "Camera.h"

#include <aurora-engine/Objects/GameObject.h>
#include <aurora-engine/BaseComponents/Transform.h>

Camera::Camera(/* args */)
{
    name = "Camera";
    near = 0.1f;
    far = 100.0f;
    fov = 45.0f;
}

Camera::~Camera()
{
}

void Camera::Start()
{
    GameObject *parent = this->GetParent();
    parent->Require(&transform);
}
