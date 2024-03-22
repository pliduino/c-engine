#include "Transform.h"

#include <iostream>
#include <format>

Transform::Transform(/* args */)
{
    name = "Transform";
    position = Vector3();
    rotation = Quaternion();
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