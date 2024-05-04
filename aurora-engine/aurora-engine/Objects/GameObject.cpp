#include "GameObject.h"

#include <aurora-engine/Objects/Component.h>

GGameObject::GGameObject()
{
    Name = "No name";
}

GGameObject::GGameObject(std::string name)
{
    this->Name = name;
}

GGameObject::~GGameObject()
{
    for (int i = 0; i < Components.size(); i++)
    {
        delete Components[i];
    }
}

std::vector<Borrow<CComponent>> GGameObject::GetComponents()
{
    return Components;
}
