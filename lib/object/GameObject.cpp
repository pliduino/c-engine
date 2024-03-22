#include "GameObject.h"

#include "Component.h"

GameObject::GameObject()
{
    name = "No name";
}

GameObject::GameObject(std::string name)
{
    this->name = name;
}

GameObject::~GameObject()
{
    for (int i = 0; i < components.size(); i++)
    {
        delete components[i];
    }
}

std::vector<Borrow<Component>> GameObject::GetComponents()
{
    return components;
}

void GameObject::AddComponent(Owner<Component> component)
{
    if (component == NULL || component->GetParent() != NULL)
    {
        return;
    }

    component->SetParent(this);
    components.push_back(component);
    return;
}
