#pragma once

#include "coordinate.hpp"

class Quaternion {
public:
    Quaternion(double x = 0, double y = 0, double z = 0, double w = 1);
    Quaternion(Vec3f v, double w);

    Vec3f v;
    double w;

    Quaternion operator* (const Quaternion &other) const;
    Vec3f rotate(const Vec3f &p) const;
};