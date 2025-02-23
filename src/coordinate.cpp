#include "coordinate.hpp"

Vec3f::Vec3f(double x, double y, double z) : x(x), y(y), z(z) {}

Vec3f Vec3f::operator+(const Vec3f& other) const {
    return Vec3f(x + other.x, y + other.y, z + other.z);
}

Vec3f Vec3f::operator-(const Vec3f& other) const {
    return Vec3f(x - other.x, y - other.y, z - other.z);
}

double Vec3f::operator* (const Vec3f &other) const {
    return x * other.x + y * other.y + z * other.z;
}

Vec3f Vec3f::cross(const Vec3f &other) const {
    return {z * other.y - y * other.z, x * other.z - z * other.x, y * other.x - x * other.y};
}

Vec3f Vec3f::operator/ (const Vec3f &other) const {
    return {x / other.x, y / other.y, z / other.z};
}

Vec3f Vec3f::operator*(double value) const {
    return Vec3f(x * value, y * value, z * value);
}
