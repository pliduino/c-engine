#pragma once

#include <string>
#include <vector>

#include <aurora-engine/Objects/Component.h>
#include <aurora-engine/BaseComponents/Transform.h>
#include <aurora-engine/Render/Material.h>

class ObjReader;

enum class EModelType
{
    Static = 0,
    Dynamic = 1,
};

class CModelRenderer : public CComponent
{
private:
    /* data */
public:
    TMaterial *Material;
    ObjReader *Model;

    EModelType Type;
    CModelRenderer(/* args */);
    ~CModelRenderer();

    CTransform *Transform;

    virtual void Start() override;
};