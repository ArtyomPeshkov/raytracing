#pragma once

#include "coordinate.hpp"
#include "quaternion.hpp"

class Ray {
public:
    Ray(Vec3f o, Vec3f d);

    const Vec3f o, d;

    Ray rotate(const Quaternion &rotation) const;
};