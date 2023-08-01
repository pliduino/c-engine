#include "Vector3.h"

#include <sstream>

Vector3::Vector3()
{
    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;
}

Vector3::Vector3(double scale)
{
    this->x = scale;
    this->y = scale;
    this->z = scale;
}

Vector3::Vector3(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3 Vector3::operator+(const Vector3 &vector)
{
    Vector3 result;
    result.x = this->x + vector.x;
    result.y = this->y + vector.y;
    result.z = this->z + vector.z;

    return result;
}

Vector3 Vector3::operator-(const Vector3 &vector)
{
    Vector3 result;
    result.x = this->x - vector.x;
    result.y = this->y - vector.y;
    result.z = this->z - vector.z;

    return result;
}

Vector3 Vector3::operator/(const float &f)
{
    Vector3 result;
    result.x = this->x / f;
    result.y = this->y / f;
    result.z = this->z / f;

    return result;
}

// Vector3::operator Vector2()
// {
//     Vector2 result;
//     result.x = this->x;
//     result.y = this->y;

std::ostream &operator<<(std::ostream &os, const Vector3 &v)
{
    os << "{ " << v.x << ", " << v.y << ", " << v.z << " }";

    return os;
}

//     return result;
// }
