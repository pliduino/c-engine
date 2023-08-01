#include "Component.h"
#include "GameObject.h"

void Component::Start()
{
}

void Component::Update()
{
}

Component::Component()
{
    parent = NULL;
}

Component::~Component()
{
}

GameObject *Component::GetParent()
{
    return parent;
}

void Component::SetParent(GameObject *new_parent)
{
    if (parent != NULL)
    {
    }
    parent = new_parent;
}