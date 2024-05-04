#include "Component.h"

#include <aurora-engine/Objects/GameObject.h>

void CComponent::Start()
{
}

void CComponent::Update()
{
}

std::string CComponent::GetName()
{
    return this->Name;
}

CComponent::CComponent()
{
    Name = "Generic Component";
    Parent = NULL;
}

CComponent::~CComponent()
{
}

GGameObject *CComponent::GetParent()
{
    return Parent;
}

void CComponent::SetParent(GGameObject *new_parent)
{
    if (Parent != NULL)
    {
    }
    Parent = new_parent;
}