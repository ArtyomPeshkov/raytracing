#pragma once

#include "coordinate.hpp"
#include "quaternion.hpp"

class Ray {
public:
    Vec3f o, d;

    Ray(Vec3f o, Vec3f d);
    Ray() = default;

    Ray operator+ (const Vec3f &p) const;
    Ray operator- (const Vec3f &p) const;
    Ray rotate(const Quaternion &r) const;
};