#include "quaternion.hpp"

Quaternion::Quaternion(float x, float y, float z, float w): v({x, y, z}), w(w) {};
Quaternion::Quaternion(Vec3f v, float w): v(v), w(w) {};

Quaternion Quaternion::operator* (const Quaternion &other) const {
    return {other.v * w + v * other.w + (v.cross(other.v)), w * other.w - v * other.v};
}

Vec3f Quaternion::rotate(const Vec3f &p) const {
    return (Quaternion(v, w) * Quaternion(p.x, p.y, p.z, 0.) * Quaternion(v * -1, w)).v;
}
