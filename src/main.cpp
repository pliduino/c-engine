#include <iostream>
#include <string>

#include "Camera.h"
#include "Scene.h"
#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "Render.h"
#include "ModelRenderer.h"
#include "ObjReader.h"
#include "Oscilator.h"
#include "BoxCollider.h"

int main(int argc, char const *argv[])
{
    Scene *scene = new Scene();

    GameObject *testObject = new GameObject();
    ModelRenderer *model = new ModelRenderer();
    model->model->ReadFile("models/cubeblender.obj");
    model->shader = std::string("shaders/vertex.glsl");
    model->fragShader = std::string("shaders/fragment.glsl");
    testObject->AddComponent(model);

    GameObject *testObject2 = new GameObject();
    ModelRenderer *model2 = new ModelRenderer();
    model2->model->ReadFile("models/cube.obj");
    model2->shader = std::string("shaders/vertex.glsl");
    model2->fragShader = std::string("shaders/fragment.glsl");
    testObject2->AddComponent(model2);
    testObject2->AddComponent(new Oscilator(0.01, 3));
    // testObject2->AddComponent(new BoxCollider());

    GameObject *cameraObj = new GameObject();
    Camera *camera = new Camera();
    cameraObj->AddComponent(camera);

    scene->objects.push_back(testObject);
    scene->objects.push_back(testObject2);
    scene->objects.push_back(cameraObj);
    scene->mainCamera = camera;

    scene->Start();

    camera->transform->position = Vector3(0.0, 0.0, 5.0);
    model->transform->position = Vector3(0.0, 2.0, 0.0);
    model->transform->scale = Vector3(0.1);
    model2->transform->position = Vector3(3.0, 0.0, 0.0);

    Render *renderer = (new Render())->HideFps();

    renderer->render(scene);

    delete renderer;
    delete scene;
    return 0;
}
