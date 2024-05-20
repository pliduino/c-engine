#include "Transform.h"

#include <iostream>
#include <format>

CTransform::CTransform(/* args */)
{
    Name = "Transform";
    Position = TVector3();
    Rotation = TQuaternion();
    Scale = TVector3(1.0, 1.0, 1.0);
}

CTransform::~CTransform()
{
}

std::ostream &operator<<(std::ostream &os, const CTransform &t)
{
    os << "Transform{ position: " << t.Position << " rotation: " << t.Rotation << " scale: " << t.Scale << " }";
    return os;
}

void CTransform::Start()
{
}

void CTransform::Update()
{
}