#pragma once

#include <string>
#include <iostream>

struct Vector3;

struct Quaternion
{
    double w, x, y, z;

    Quaternion();
    Quaternion(double w, double x, double y, double z);

    static Quaternion FromEulerAngle(const double roll, const double pitch, const double yaw);
    Vector3 ToEulerAngle();
    friend std::ostream &operator<<(std::ostream &os, const Quaternion &q);
    Vector3 operator*(const Vector3 &v);
    Quaternion operator*(const Quaternion &q);
    Quaternion &operator*=(const Quaternion &q);
};