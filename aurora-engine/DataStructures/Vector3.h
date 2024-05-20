#pragma once

#include <string>
#include <iostream>

// #include "./Vector2.h"

struct TVector3
{
    double x, y, z;

    TVector3();
    TVector3(double scale);
    TVector3(double x, double y, double z);

    TVector3 operator+(const TVector3 &vector);
    TVector3 operator-(const TVector3 &vector);
    TVector3 operator/(const float &f);
    // operator Vector2();
    friend std::ostream &operator<<(std::ostream &os, const TVector3 &v);
};
