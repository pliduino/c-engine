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
    return this->name;
}

CComponent::CComponent()
{
    name = "Generic Component";
    parent = NULL;
}

CComponent::~CComponent()
{
}

GameObject *CComponent::GetParent()
{
    return parent;
}

void CComponent::SetParent(GameObject *new_parent)
{
    if (parent != NULL)
    {
    }
    parent = new_parent;
}