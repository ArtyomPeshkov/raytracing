#include "ray.hpp"

Ray::Ray(Vec3f o, Vec3f d): o(o), d(d) {};

Ray Ray::rotate(const Quaternion &rotation) const {
    return {rotation.rotate(o), rotation.rotate(d)};
}