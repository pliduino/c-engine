#pragma once

#include <string>

class GameObject;

class Component
{
private:
    GameObject *parent;

protected:
    std::string name;

public:
    Component(/* args */);
    virtual ~Component();

    virtual void Start(void);
    virtual void Update(void);

    GameObject *GetParent();
    void SetParent(GameObject *parent);
};