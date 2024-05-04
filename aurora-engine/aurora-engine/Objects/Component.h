#pragma once

#include <string>

class GameObject;

class CComponent
{
private:
    GameObject *parent;

protected:
    std::string name;

public:
    CComponent(/* args */);
    virtual ~CComponent();

    virtual void Start(void);
    virtual void Update(void);
    std::string GetName();

    GameObject *GetParent();
    void SetParent(GameObject *parent);
};