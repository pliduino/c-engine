#include "Vector3.h"

#include <sstream>

TVector3::TVector3()
{
    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;
}

TVector3::TVector3(double scale)
{
    this->x = scale;
    this->y = scale;
    this->z = scale;
}

TVector3::TVector3(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

TVector3 TVector3::operator+(const TVector3 &vector)
{
    TVector3 result;
    result.x = this->x + vector.x;
    result.y = this->y + vector.y;
    result.z = this->z + vector.z;

    return result;
}

TVector3 TVector3::operator-(const TVector3 &vector)
{
    TVector3 result;
    result.x = this->x - vector.x;
    result.y = this->y - vector.y;
    result.z = this->z - vector.z;

    return result;
}

TVector3 TVector3::operator/(const float &f)
{
    TVector3 result;
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

std::ostream &operator<<(std::ostream &os, const TVector3 &v)
{
    os << "{ " << v.x << ", " << v.y << ", " << v.z << " }";

    return os;
}

//     return result;
// }
