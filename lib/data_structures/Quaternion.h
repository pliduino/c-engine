#pragma once

#include <string>
#include <iostream>

struct Quaternion
{
    double x, y, z, w;

    friend std::ostream &operator<<(std::ostream &os, const Quaternion &q);
};
