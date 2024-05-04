#include "ModelRenderer.h"

#include <iostream>

#include <aurora-engine/Reading/ObjReader.h>
#include <aurora-engine/Objects/GameObject.h>
#include <aurora-engine/BaseComponents/Transform.h>

CModelRenderer::CModelRenderer(/* args */)
{
    Name = "ModelRenderer";
    Model = new ObjReader();
}

CModelRenderer::~CModelRenderer()
{
    delete this->Model;
}

void CModelRenderer::Start()
{
    GetParent()->Require(&Transform);
}
