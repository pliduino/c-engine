#include "Quaternion.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <aurora-engine/DataStructures/Vector3.h>

std::ostream &operator<<(std::ostream &os, const TQuaternion &q)
{
    os << "{ " << q.x << ", " << q.y << ", " << q.z << ", " << q.w << " }";

    return os;
}

TVector3 TQuaternion::ToEulerAngle()
{
    TVector3 eulerAngle;

    double sinr_cosp = 2 * (this->w * this->x + this->y * this->z);
    double cosr_cosp = 1 - 2 * (this->x * this->x + this->y * this->y);
    eulerAngle.x = std::atan2(sinr_cosp, cosr_cosp);

    // pitch (y-axis rotation)
    double sinp = std::sqrt(1 + 2 * (this->w * this->y - this->x * this->z));
    double cosp = std::sqrt(1 - 2 * (this->w * this->y - this->x * this->z));
    eulerAngle.y = 2 * std::atan2(sinp, cosp) - M_PI / 2;

    // yaw (z-axis rotation)
    double siny_cosp = 2 * (this->w * this->z + this->x * this->y);
    double cosy_cosp = 1 - 2 * (this->y * this->y + this->z * this->z);
    eulerAngle.z = std::atan2(siny_cosp, cosy_cosp);

    return eulerAngle;
}

TVector3 TQuaternion::operator*(const TVector3 &v)
{
    TVector3 rotatedVector;
    TQuaternion convertedVector = TQuaternion(0, v.x, v.y, v.z);

    rotatedVector.x = v.x;

    return rotatedVector;
}

TQuaternion TQuaternion::operator*(const TQuaternion &q)
{
    TQuaternion newQuaternion;
    newQuaternion.w = (this->w * q.w) - (this->x * q.x) - (this->y * q.y) - (this->z * q.z);
    newQuaternion.x = (this->w * q.x) + (this->x * q.w) + (this->y * q.z) - (this->z * q.y);
    newQuaternion.y = (this->w * q.y) - (this->x * q.z) + (this->y * q.w) + (this->z * q.x);
    newQuaternion.z = (this->w * q.z) + (this->x * q.y) - (this->y * q.x) + (this->z * q.w);
    return newQuaternion;
}

TQuaternion &TQuaternion::operator*=(const TQuaternion &q)
{
    TQuaternion newValue = *this * q;

    this->w = newValue.w;
    this->x = newValue.x;
    this->y = newValue.y;
    this->z = newValue.z;

    return *this;
}

TQuaternion::TQuaternion()
{
    this->w = 0;
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

TQuaternion::TQuaternion(double w, double x, double y, double z)
{
    this->w = w;
    this->x = x;
    this->y = y;
    this->z = z;
}

TQuaternion TQuaternion::FromEulerAngle(const double roll, const double pitch, const double yaw)
{
    double cr = cos(roll * 0.5);
    double sr = sin(roll * 0.5);
    double cp = cos(pitch * 0.5);
    double sp = sin(pitch * 0.5);
    double cy = cos(yaw * 0.5);
    double sy = sin(yaw * 0.5);

    TQuaternion q;
    q.w = cr * cp * cy + sr * sp * sy;
    q.x = sr * cp * cy - cr * sp * sy;
    q.y = cr * sp * cy + sr * cp * sy;
    q.z = cr * cp * sy - sr * sp * cy;

    return q;
}