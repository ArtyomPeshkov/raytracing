#pragma once

#include "coordinate.hpp"

class Quaternion {
public:
    Quaternion(float x = 0.0, float y = 0.0, float z = 0.0, float w = 1.0);
    Quaternion(Vec3f v, float w);

    Vec3f v;
    float w;

    Quaternion operator* (const Quaternion &other) const;
    Vec3f rotate(const Vec3f &p) const;
};
