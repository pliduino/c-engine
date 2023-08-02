#pragma once

#include <string>
#include <vector>

class Transform;
class Component;

class GameObject
{
private:
    std::string name;
    std::vector<Component *> components;

public:
    GameObject(/* args */);
    ~GameObject();

    std::vector<Component *> GetComponents();

    template <class T>
    std::vector<T *> GetComponents();

    template <class T>
    T *GetComponent();

    template <class T>
    bool TryGetComponent(T *&component);

    template <class T>
    void Require(T **arg);

    template <class... R>
    void Require(R... args);

    void AddComponent(Component *component);
};

template <class T>
T *GameObject::GetComponent()
{
    T *value;
    for (auto &component : components)
    {
        value = dynamic_cast<T *>(component);

        if (value != NULL)
            return value;
    }

    return NULL;
}

template <class T>
std::vector<T *> GameObject::GetComponents()
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
void GameObject::Require(T **arg)
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