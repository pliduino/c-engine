#pragma once

#include <string>
#include <vector>
#include <aurora-engine/Pointers/Pointers.h>

class CTransform;
class CComponent;

class GGameObject
{
private:
    std::vector<Owner<CComponent>> Components;

public:
    std::string Name;

    GGameObject(/* args */);
    GGameObject(std::string name);
    ~GGameObject();

    std::vector<Borrow<CComponent>> GetComponents();

    template <class T>
    std::vector<Borrow<T>> GetComponents();

    template <class T>
    Borrow<T> GetComponent();

    // template <class T>
    // bool TryGetComponent(Borrow<T> &component);

    template <class T>
    void Require(Borrow<T> *arg);

    template <class... R>
    void Require(R... args);

    template <typename T>
    Borrow<T> AddComponent(Owner<T> component)
    {
        if (component == nullptr || component->GetParent() != nullptr)
        {
            return nullptr;
        }

        component->SetParent(this);
        Components.push_back(component);
        return component;
    }

    virtual void Start(){};
};

template <class T>
Borrow<T> GGameObject::GetComponent()
{
    Borrow<T> value;
    for (auto &component : Components)
    {
        value = dynamic_cast<T *>(component);

        if (value != NULL)
            return value;
    }

    return NULL;
}

template <class T>
std::vector<Borrow<T>> GGameObject::GetComponents()
{
    std::vector<T *> componentVector = new std::vector<T *>();

    T *value;
    for (auto &component : Components)
    {
        value = dynamic_cast<T *>(component);

        if (value != NULL)
            componentVector.push_back(value);
    }

    return componentVector;
}

template <class T>
void GGameObject::Require(Borrow<T> *arg)
{
    *arg = GetComponent<T>();

    if (*arg == NULL)
    {
        *arg = new T();
        AddComponent(*arg);
    }
}

template <class... R>
void GGameObject::Require(R... args)
{
    (Require(args), ...);
}