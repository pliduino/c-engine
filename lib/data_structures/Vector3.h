#pragma once

#include <string>
#include <iostream>

// #include "./Vector2.h"

struct Vector3
{
    double x, y, z;

    Vector3();
    Vector3(double scale);
    Vector3(double x, double y, double z);

    Vector3 operator+(const Vector3 &vector);
    Vector3 operator-(const Vector3 &vector);
    Vector3 operator/(const float &f);
    // operator Vector2();
    friend std::ostream &operator<<(std::ostream &os, const Vector3 &v);
};
