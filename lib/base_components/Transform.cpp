#include "Transform.h"

#include <iostream>

Transform::Transform(/* args */)
{
    position = Vector3();
    rotation = {0};
    scale = Vector3(1.0, 1.0, 1.0);
}

Transform::~Transform()
{
}

std::ostream &operator<<(std::ostream &os, const Transform &t)
{
    os << "Transform{ position: " << t.position << " rotation: " << t.rotation << " scale: " << t.scale << " }";
    return os;
}

void Transform::Start()
{
}

void Transform::Update()
{
}
