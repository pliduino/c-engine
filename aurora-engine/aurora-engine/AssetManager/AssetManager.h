#pragma once

#include <map>
#include <string>

#include <aurora-engine/Render/Material.h>
#include <aurora-engine/Pointers/Pointers.h>
#include <aurora-engine/Objects/GameObject.h>

class AssetManager
{
    std::map<std::string, GGameObject> DefaultObjects;
    std::map<std::string, TSharedPointer<TMaterial>> Materials;

public:
    template <typename T>
    T *GetDefaultObject(std::string Name)
    {
        auto foundObject = DefaultObjects.find(Name);
        if (foundObject == DefaultObjects.end())
        {
            return nullptr;
        }

        T *casted = dynamic_cast<T *>(&(foundObject->second));
        if (casted == nullptr)
        {
            std::cerr << "Found object however it appears to be of a different type, perhaps there are 2 objects with the same name\n";
        }
        return casted;
    }
};

AssetManager *gManager = new AssetManager();