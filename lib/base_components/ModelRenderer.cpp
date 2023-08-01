#include "ModelRenderer.h"

#include "GameObject.h"
#include "Transform.h"
#include "iostream"

ModelRenderer::ModelRenderer(/* args */)
{
    vertexData = std::vector<float>();
}

ModelRenderer::~ModelRenderer()
{
}

void ModelRenderer::Start()
{
    GameObject *parent = this->GetParent();
    parent->Require(&transform);
}
