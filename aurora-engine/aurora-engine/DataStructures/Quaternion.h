#pragma once

#include <string>
#include <iostream>

struct TVector3;

struct TQuaternion
{
    double w, x, y, z;

    TQuaternion();
    TQuaternion(double w, double x, double y, double z);

    static TQuaternion FromEulerAngle(const double roll, const double pitch, const double yaw);
    TVector3 ToEulerAngle();
    friend std::ostream &operator<<(std::ostream &os, const TQuaternion &q);
    TVector3 operator*(const TVector3 &v);
    TQuaternion operator*(const TQuaternion &q);
    TQuaternion &operator*=(const TQuaternion &q);
};