#include "Quaternion.h"

std::ostream &operator<<(std::ostream &os, const Quaternion &q)
{
    os << "{ " << q.x << ", " << q.y << ", " << q.z << ", " << q.w << " }";

    return os;
}

Quaternion Quaternion::FromEulerAngle(const double roll, const double pitch, const double yaw)
{
    double cr = cos(roll * 0.5);
    double sr = sin(roll * 0.5);
    double cp = cos(pitch * 0.5);
    double sp = sin(pitch * 0.5);
    double cy = cos(yaw * 0.5);
    double sy = sin(yaw * 0.5);

    Quaternion q;
    q.w = cr * cp * cy + sr * sp * sy;
    q.x = sr * cp * cy - cr * sp * sy;
    q.y = cr * sp * cy + sr * cp * sy;
    q.z = cr * cp * sy - sr * sp * cy;

    return q;
}