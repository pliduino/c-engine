#pragma once

#include <string>
#include <iostream>

struct Quaternion
{
    double w, x, y, z;

    static Quaternion FromEulerAngle(const double roll, const double pitch, const double yaw);
    friend std::ostream &operator<<(std::ostream &os, const Quaternion &q);
};