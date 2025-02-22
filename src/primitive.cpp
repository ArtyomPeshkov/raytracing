#include "primitive.hpp"
#include "utils.hpp"

#include <cmath>

Ellipsoid::Ellipsoid(Vec3f r): radius(r) {}
Plane::Plane(Vec3f n): normal(n) {}
Box::Box(Vec3f s): size(s) {}

std::optional<std::pair<float, Color>> Primitive::getIntersection(const Ray &ray) {
    std::optional<float> point = intersection(Ray(ray.o - position, ray.d).rotate(rotation));
    if (point.has_value()) {
        return std::make_pair(point.value(), color);
    }
    return {};
}

std::optional<float> Ellipsoid::intersection(const Ray &ray) const {
    float a = (ray.d / radius) * (ray.d / radius);
    float b = (ray.o / radius) * (ray.d / radius) * 2;
    float c = (ray.o / radius) * (ray.o / radius) - 1;
    return getCorrectRoot(solveEq(a, b, c));
}

std::optional<float> Plane::intersection(const Ray &ray) const {
    float t = -1 * (ray.o * normal) / (ray.d * normal);
    return {getCorrectRoot({t, t})};
}

std::optional<float> Box::intersection(const Ray &ray) const {
    Vec3f t1 = (size - ray.o) / ray.d;
    Vec3f t2 = (size * (-1) - ray.o) / ray.d;

    float root1 = std::max(std::max(std::min(t1.x, t2.x), std::min(t1.y, t2.y)), std::min(t1.z, t2.z));
    float root2 = std::min(std::min(std::max(t1.x, t2.x), std::max(t1.y, t2.y)), std::max(t1.z, t2.z));

    if (root1 > root2 || root2 < 0) {
        return {};
    } else if (root1 < 0) {
        return root2;
    }
    return root1;
}