#include "ModelRenderer.h"

#include <iostream>

#include "ObjReader.h"
#include "GameObject.h"
#include "Transform.h"

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
