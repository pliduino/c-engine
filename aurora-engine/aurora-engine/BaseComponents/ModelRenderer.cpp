#include "ModelRenderer.h"

#include <iostream>

#include <aurora-engine/Reading/ObjReader.h>
#include <aurora-engine/Objects/GameObject.h>
#include <aurora-engine/BaseComponents/Transform.h>

ModelRenderer::ModelRenderer(/* args */)
{
    name = "ModelRenderer";
    model = new ObjReader();
}

ModelRenderer::~ModelRenderer()
{
    delete this->model;
}

void ModelRenderer::Start()
{
    GetParent()->Require(&transform);
}
