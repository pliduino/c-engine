#include "Scene.h"

#include <aurora-engine/Objects/GameObject.h>
#include <aurora-engine/Objects/Component.h>

Scene::Scene(/* args */)
{
}

Scene::~Scene()
{
    for (int i = 0; i < objects.size(); i++)
    {
        delete objects[i];
    }
}

void Scene::Start()
{
    for (int i = 0; i < objects.size(); i++)
    {
        auto components = objects[i]->GetComponents();
        for (int j = 0; j < components.size(); j++)
        {
            components[j]->Start();
        }
    }
}

void Scene::Update()
{
    // Check Collisions

    for (int i = 0; i < objects.size(); i++)
    {
        auto components = objects[i]->GetComponents();
        for (int j = 0; j < components.size(); j++)
        {
            components[j]->Update();
        }
    }
}
