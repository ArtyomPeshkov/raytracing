#include "primitive.hpp"
#include "utils.hpp"

#include <cmath>

Ellipsoid::Ellipsoid(Vec3f r): radius(r) {}
Plane::Plane(Vec3f n): normal(n) {}
Box::Box(Vec3f s): size(s) {}

std::optional<std::pair<double, Color>> Primitive::getIntersection(const Ray &ray) {
    std::optional<double> point = intersection(Ray(ray.o - position, ray.d).rotate(rotation));
    if (point.has_value()) {
        return std::make_pair(point.value(), color);
    }
    return {};
}

std::optional<double> Ellipsoid::intersection(const Ray &ray) const {
    double a = (ray.d / radius) * (ray.d / radius);
    double b = (ray.o / radius) * (ray.d / radius) * 2;
    double c = (ray.o / radius) * (ray.o / radius) - 1;
    return getCorrectRoot(solveEq(a, b, c));
}

std::optional<double> Plane::intersection(const Ray &ray) const {
    double t = -1.0 * (ray.o * normal) / (ray.d * normal);
    return {getCorrectRoot({t, t})};
}

std::optional<double> Box::intersection(const Ray &ray) const {
    Vec3f t1 = (size - ray.o) / ray.d;
    Vec3f t2 = (size * (-1.0) - ray.o) / ray.d;

    double root1 = std::max(std::max(std::min(t1.x, t2.x), std::min(t1.y, t2.y)), std::min(t1.z, t2.z));
    double root2 = std::min(std::min(std::max(t1.x, t2.x), std::max(t1.y, t2.y)), std::max(t1.z, t2.z));

    if (root1 > root2 || root2 < 0) {
        return {};
    } else if (root1 < 0) {
        return root2;
    }
    return root1;
}