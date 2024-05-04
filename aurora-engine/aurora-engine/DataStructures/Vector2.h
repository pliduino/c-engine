#pragma once

#include <string>

// #include "./Vector3.h"

struct Vector2
{
    double x, y;

    Vector2();
    Vector2(double x, double y);

    std::string to_string();
    Vector2 operator+(const Vector2 &vector);
    Vector2 operator-(const Vector2 &vector);
    // operator Vector3();
};
