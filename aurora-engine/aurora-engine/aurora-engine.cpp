#include <iostream>
#include <string>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <aurora-engine/Pointers/Pointers.h>

#include <aurora-engine/DataStructures/Quaternion.h>
#include <aurora-engine/Objects/Scene.h>
#include <aurora-engine/Objects/GameObject.h>
#include <aurora-engine/Objects/Component.h>
#include <aurora-engine/BaseComponents/Transform.h>
#include <aurora-engine/Render/Render.h>
#include <aurora-engine/BaseComponents/ModelRenderer.h>
#include <aurora-engine/Reading/ObjReader.h>
#include <aurora-engine/Physics/Oscilator.h>
#include <aurora-engine/DataStructures/Events/Event.h>
#include <aurora-engine/Render/Material.h>
#include <aurora-engine/BaseGameObjects/Camera.h>
#include <aurora-engine/Render/Window/WindowGLFW.h>

int main(int argc, char const *argv[])
{
  TMaterial material_1 = {.VertexShader = "shaders/vertex.glsl", .FragmentShader = "shaders/fragment.glsl"};

  Scene *scene = new Scene();

  GGameObject *testObject = new GGameObject("LightSource");
  CModelRenderer *model = new CModelRenderer();
  model->Material = &material_1;
  model->Model->ReadFile("models/cubeblender.obj");
  testObject->AddComponent(model);

  GGameObject *sphereObject = new GGameObject("Sphere");
  CModelRenderer *sphereModel = new CModelRenderer();
  sphereModel->Material = &material_1;
  sphereModel->Model->ReadFile("models/sphere.obj");
  sphereObject->AddComponent(sphereModel);

  GGameObject *planeObject = new GGameObject("Plane");
  CModelRenderer *modelPlane = new CModelRenderer();
  modelPlane->Model->ReadFile("models/cube.obj");
  modelPlane->Material = &material_1;
  planeObject->AddComponent(modelPlane);

  GGameObject *testObject2 = new GGameObject("WalkingCube");
  CModelRenderer *model2 = new CModelRenderer();
  model2->Material = &material_1;
  model2->Model->ReadFile("models/cube.obj");
  testObject2->AddComponent(model2);
  testObject2->AddComponent(new Oscilator(0.01, 3));
  // testObject2->AddComponent(new BoxCollider());

  GCamera *cameraObj = new GCamera();

  scene->objects.push_back(testObject);
  scene->objects.push_back(testObject2);
  scene->objects.push_back(planeObject);
  scene->objects.push_back(sphereObject);
  scene->objects.push_back(cameraObj);
  scene->mainCamera = cameraObj;

  scene->Start();

  cameraObj->Transform->Position = TVector3(0.0, 0.0, 5.0);
  cameraObj->Transform->Rotation = TQuaternion::FromEulerAngle(0, 0, 0);
  model->Transform->Position = TVector3(0.0, 2.0, 0.0);
  model->Transform->Scale = TVector3(0.1);
  model2->Transform->Position = TVector3(3.0, 0.0, 0.0);
  model2->Transform->Rotation = TQuaternion::FromEulerAngle(45, 0, 45);
  modelPlane->Transform->Position = TVector3(0.0, -2.0, 0.0);
  modelPlane->Transform->Scale = TVector3(10, 0.01, 10);
  sphereModel->Transform->Position = TVector3(0);

  Render *renderer = (new Render(new TWindowGLFW()))->ShowFps();

  renderer->RenderScene(scene);

  delete renderer;
  delete scene;
  return 0;
}
