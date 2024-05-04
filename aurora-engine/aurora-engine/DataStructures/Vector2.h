#pragma once

#include <string>

// #include "./Vector3.h"

struct TVector2
{
    double x, y;

    TVector2();
    TVector2(double x, double y);

    std::string to_string();
    TVector2 operator+(const TVector2 &vector);
    TVector2 operator-(const TVector2 &vector);
    // operator Vector3();
};
