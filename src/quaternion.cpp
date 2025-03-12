#include "quaternion.hpp"

Quaternion::Quaternion(double x, double y, double z, double w): v({x, y, z}), w(w) {};
Quaternion::Quaternion(Vec3f v, double w): v(v), w(w) {};

Quaternion Quaternion::operator* (const Quaternion &other) const {
    return {w * other.v + other.w * v + v.cross(other.v), w * other.w - v * other.v};
}

Vec3f Quaternion::rotate(const Vec3f &p) const {
    return (Quaternion(v, w) * Quaternion(p.x, p.y, p.z, 0.0) * Quaternion(-1.0 * v, w)).v;
}
