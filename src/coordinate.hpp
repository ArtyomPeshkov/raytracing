#pragma once
#include <istream>

class Vec3f {
public:
    Vec3f(float x = 0.0, float y = 0.0, float z = 0.0);

    float x;
    float y;
    float z;

    Vec3f operator+(const Vec3f& other) const;
    Vec3f operator-(const Vec3f& other) const;
    float operator*(const Vec3f& other) const;
    Vec3f cross(const Vec3f& other) const;
    Vec3f normalized() const;
    Vec3f operator/(const Vec3f& other) const;
    float self_dot() const;
};

Vec3f operator* (float k, const Vec3f &p);
