#include "Quaternion.h"

std::ostream &operator<<(std::ostream &os, const Quaternion &q)
{
    os << "{ " << q.x << ", " << q.y << ", " << q.z << ", " << q.w << " }";

    return os;
}
