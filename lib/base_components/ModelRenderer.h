#pragma once

#include <string>
#include <vector>

#include "Component.h"
#include "Transform.h"

enum ModelType
{
    Static = 0,
    Dynamic = 1,
};

class ModelRenderer : public Component
{
private:
    /* data */
public:
    std::string shader;
    std::string fragShader;
    std::vector<float> vertexData;

    ModelType type;
    ModelRenderer(/* args */);
    ~ModelRenderer();

    Transform *transform;

    void Start() override;
};