#include "GameObject.h"

#include "Component.h"

GameObject::GameObject()
{
    name = "No name";
}

GameObject::~GameObject()
{
    for (int i = 0; i < components.size(); i++)
    {
        delete components[i];
    }
}

std::vector<Component *> GameObject::GetComponents()
{
    return components;
}

void GameObject::AddComponent(Component *component)
{
    if (component == NULL || component->GetParent() != NULL)
    {
        return;
    }

    component->SetParent(this);
    components.push_back(component);
    return;
}
