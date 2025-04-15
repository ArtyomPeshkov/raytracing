#include "primitive.hpp"
#include "utils.hpp"

#include <cmath>

std::optional <Intersection> Primitive::intersection(const Ray &ray) {
    auto point = intersect((ray - position).rotate(rotation));
    if (!point.has_value()) {
        return {};
    }

    auto [inter_normal, is_in, t, inter_color, index] = point.value();
    return {Intersection(t, is_in, Quaternion(-1.0 * rotation.v, rotation.w).rotate(inter_normal).normalized(), color, -1)};
}

Primitive::Primitive(Vec3f data, PrimitiveType type): data(data), type(type) {}

std::optional<Intersection> Primitive::intersect(const Ray &ray) const {
    if (type == PrimitiveType::BOX) {
        return intersectBox(ray);
    } else if (type == PrimitiveType::PLANE) {
        return intersectPlane(ray);
    } else {
        return intersectEllipsoid(ray);
    }
}

std::optional<Intersection> Primitive::intersectEllipsoid(const Ray& ray) const {
    double a = (ray.d / data) * ((ray.d / data));
    double b = 2.0 * (ray.o / data) * ((ray.d / data));
    double c = (ray.o / data) * ((ray.o / data)) - 1.0;

    auto opt_t = getCorrectRoot(solveEq(a, b, c));
    if (!opt_t.has_value()) {
        return {};
    }

    auto [inter_normal, is_in, t, inter_color, index] = opt_t.value();
    Vec3f square_data = Vec3f(data.x * data.x, data.y * data.y, data.z * data.z);
    inter_normal = (is_in ? -1.0 : 1.0) * ((ray.o + t * ray.d) / square_data).normalized();
    return Intersection(t, is_in, inter_normal, color);
}

std::optional <Intersection> Primitive::intersectPlane(const Ray &ray) const {
    double t = -1.0 * (ray.o * data) / (ray.d * data);
    if (t <= 0) {
        return{};
    }

    bool is_in = ray.d * data > 0;
    return Intersection(t, is_in, (is_in ? -1.0 : 1.0) * data, color);

}

std::optional<Intersection> Primitive::intersectBox(const Ray& ray) const {
    Vec3f t1 = (data - ray.o) / ray.d;
    Vec3f t2 = (-1.0 * data - ray.o) / ray.d;

    double root1 = std::max(std::max(std::min(t1.x, t2.x), std::min(t1.y, t2.y)), std::min(t1.z, t2.z));
    double root2 = std::min(std::min(std::max(t1.x, t2.x), std::max(t1.y, t2.y)), std::max(t1.z, t2.z));

    if (root1 > root2 || root2 < 0) {
        return {};
    }

    double t = (root1 < 0) ? root2 : root1;
    bool is_in = (root1 < 0);
    Vec3f inter_normal = (is_in ? -1.0 : 1.0) * (ray.o + t * ray.d) / data;

    double mx = std::max(std::max(std::abs(inter_normal.x), std::abs(inter_normal.y)), std::abs(inter_normal.z));
    inter_normal.x = (std::abs(inter_normal.x) == mx) ? sign(inter_normal.x) : 0.0;
    inter_normal.y = (std::abs(inter_normal.y) == mx) ? sign(inter_normal.y) : 0.0;
    inter_normal.z = (std::abs(inter_normal.z) == mx) ? sign(inter_normal.z) : 0.0;

    return Intersection(t, is_in, inter_normal, color);
}
