#include <iostream>
#include <string>

#include "Quaternion.h"
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

    GameObject *testObject = new GameObject("LightSource");
    ModelRenderer *model = new ModelRenderer();
    model->model->ReadFile("models/cubeblender.obj");
    model->shader = std::string("shaders/vertex.glsl");
    model->fragShader = std::string("shaders/fragment.glsl");
    testObject->AddComponent(model);

    GameObject *sphereObject = new GameObject("Sphere");
    ModelRenderer *sphereModel = new ModelRenderer();
    sphereModel->model->ReadFile("models/sphere.obj");
    sphereModel->shader = std::string("shaders/vertex.glsl");
    sphereModel->fragShader = std::string("shaders/fragment.glsl");
    sphereObject->AddComponent(sphereModel);

    GameObject *planeObject = new GameObject("Plane");
    ModelRenderer *modelPlane = new ModelRenderer();
    modelPlane->model->ReadFile("models/cube.obj");
    modelPlane->shader = std::string("shaders/vertex.glsl");
    modelPlane->fragShader = std::string("shaders/fragment2.glsl");
    planeObject->AddComponent(modelPlane);

    GameObject *testObject2 = new GameObject("WalkingCube");
    ModelRenderer *model2 = new ModelRenderer();
    model2->model->ReadFile("models/cube.obj");
    model2->shader = std::string("shaders/vertex.glsl");
    model2->fragShader = std::string("shaders/fragment.glsl");
    testObject2->AddComponent(model2);
    testObject2->AddComponent(new Oscilator(0.01, 3));
    testObject2->AddComponent(new BoxCollider());

    GameObject *cameraObj = new GameObject("Camera");
    Camera *camera = new Camera();
    cameraObj->AddComponent(camera);

    scene->objects.push_back(testObject);
    scene->objects.push_back(testObject2);
    scene->objects.push_back(planeObject);
    scene->objects.push_back(sphereObject);
    scene->objects.push_back(cameraObj);
    scene->mainCamera = camera;

    scene->Start();

    camera->transform->position = Vector3(0.0, 0.0, 5.0);
    camera->transform->rotation = Quaternion::FromEulerAngle(0, 0, 0);
    model->transform->position = Vector3(0.0, 2.0, 0.0);
    model->transform->scale = Vector3(0.1);
    model2->transform->position = Vector3(3.0, 0.0, 0.0);
    model2->transform->rotation = Quaternion::FromEulerAngle(45, 0, 45);
    modelPlane->transform->position = Vector3(0.0, -2.0, 0.0);
    modelPlane->transform->scale = Vector3(10, 0.01, 10);
    sphereModel->transform->position = Vector3(0);

    Render *renderer = (new Render())->ShowFps();

    renderer->render(scene);

    delete renderer;
    delete scene;
    return 0;
}
