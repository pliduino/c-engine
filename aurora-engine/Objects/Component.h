#pragma once

#include <string>

class GGameObject;

class CComponent
{
private:
    GGameObject *Parent;

protected:
    std::string Name;

public:
    CComponent(/* args */);
    virtual ~CComponent();

    virtual void Start();
    virtual void Update();
    std::string GetName();

    GGameObject *GetParent();
    void SetParent(GGameObject *parent);
};