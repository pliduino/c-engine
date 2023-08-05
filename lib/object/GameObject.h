#pragma once

#include <string>
#include <vector>

#include "pointers.h"

class Transform;
class Component;

class GameObject
{
private:
    std::vector<Owner<Component>> components;

public:
    std::string name;

    GameObject(/* args */);
    GameObject(std::string name);
    ~GameObject();

    std::vector<Borrow<Component>> GetComponents();

    template <class T>
    std::vector<Borrow<T>> GetComponents();

    template <class T>
    Borrow<T> GetComponent();

    template <class T>
    bool TryGetComponent(Borrow<T> &component);

    template <class T>
    void Require(Borrow<T> *arg);

    template <class... R>
    void Require(R... args);

    void AddComponent(Owner<Component> component);
};

template <class T>
Borrow<T> GameObject::GetComponent()
{
    Borrow<T> value;
    for (auto &component : components)
    {
        value = dynamic_cast<T *>(component);

        if (value != NULL)
            return value;
    }

    return NULL;
}

template <class T>
std::vector<Borrow<T>> GameObject::GetComponents()
{
    std::vector<T *> componentVector = new std::vector<T *>();

    T *value;
    for (auto &component : components)
    {
        value = dynamic_cast<T *>(component);

        if (value != NULL)
            componentVector.push_back(value);
    }

    return componentVector;
}

template <class T>
void GameObject::Require(Borrow<T> *arg)
{
    *arg = GetComponent<T>();

    if (*arg == NULL)
    {
        *arg = new T();
        AddComponent(*arg);
    }
}

template <class... R>
void GameObject::Require(R... args)
{
    (Require(args), ...);
}