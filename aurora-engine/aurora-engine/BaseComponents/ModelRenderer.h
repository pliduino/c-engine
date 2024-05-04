#pragma once

#include <string>
#include <vector>

#include <aurora-engine/Objects/Component.h>
#include <aurora-engine/BaseComponents/Transform.h>

class ObjReader;

enum ModelType
{
    Static = 0,
    Dynamic = 1,
};

class ModelRenderer : public CComponent
{
private:
    /* data */
public:
    std::string shader;
    std::string fragShader;
    ObjReader *model;

    ModelType type;
    ModelRenderer(/* args */);
    ~ModelRenderer();

    Transform *transform;

    void Start() override;
};