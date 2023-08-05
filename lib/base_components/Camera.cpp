#include "Camera.h"

#include "GameObject.h"

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
