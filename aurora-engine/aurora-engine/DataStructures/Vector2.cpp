#include "Vector2.h"

#include <iostream>
#include <sstream>
#include <string>

TVector2::TVector2()
{
    this->x = 0.0;
    this->y = 0.0;
}

TVector2::TVector2(double x, double y)
{
    this->x = x;
    this->y = y;
}

std::string TVector2::to_string()
{
    std::string result;
    std::ostringstream out;
    out << "{x: " << this->x << " y: " << this->y
        << "}\n";

    result = out.str();

    return result;
}

TVector2 TVector2::operator+(const TVector2 &vector)
{
    TVector2 result;
    result.x = this->x + vector.x;
    result.y = this->y + vector.y;

    return result;
}

TVector2 TVector2::operator-(const TVector2 &vector)
{
    TVector2 result;
    result.x = this->x + vector.x;
    result.y = this->y + vector.y;

    return result;
}

// Vector2::operator Vector3()
// {
//     Vector3 result;
//     result.x = this->x;
//     result.y = this->y;
//     result.z = 0;

//     return result;
// }