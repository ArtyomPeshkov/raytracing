#pragma once
#include <istream>

class Vec3f {
public:
    Vec3f(double x = 0, double y = 0, double z = 0);

    double x;
    double y;
    double z;

    Vec3f operator+(const Vec3f& other) const;
    Vec3f operator-(const Vec3f& other) const;
    double operator*(const Vec3f& other) const;
    Vec3f cross(const Vec3f& other) const;
    Vec3f operator/(const Vec3f& other) const;
    Vec3f operator*(double value) const;
};