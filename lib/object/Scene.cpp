#include "Scene.h"

#include "GameObject.h"
#include "Component.h"

Scene::Scene(/* args */)
{
    i = 0;
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
