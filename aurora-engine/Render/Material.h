#pragma once

#include <string>

struct TMaterial
{
    std::string VertexShader;
    std::string FragmentShader;
    bool IsLoaded;
    unsigned int Id;
};
