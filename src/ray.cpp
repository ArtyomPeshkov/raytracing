#include "ray.hpp"

Ray::Ray(Vec3f o, Vec3f d): o(o), d(d) {
    d = d.normalized();
}

Ray Ray::operator+ (const Vec3f &vec) const {
    return {o + vec, d};
}

Ray Ray::operator- (const Vec3f &vec) const {
    return {o - vec, d};
}

Ray Ray::rotate(const Quaternion &q) const {
    return {q.rotate(o), q.rotate(d)};
}
