#pragma once

#include <optional>
#include "coordinate.hpp"
#include "color.hpp"
#include "quaternion.hpp"
#include "ray.hpp"

enum class Material {
    DIFFUSE, METALLIC, DIELECTRIC
};

enum class PrimitiveType {
    PLANE, BOX, ELLIPSOID
};

struct Intersection {
    Intersection(double t = 0, bool is_in = false, Vec3f normal = Vec3f(0, 0, 0), Color color = Color(0, 0, 0), int index = -1): t(t), normal(normal), color(color), is_in(is_in), primitiveIndex(index) {};

    Vec3f normal;
    bool is_in;
    double t;
    Color color;
    int primitiveIndex;
};

class Primitive {
public:
    Vec3f position{};
    Quaternion rotation = {0, 0, 0, 1};
    Color color;
    Color emission;

    Material material = Material::DIFFUSE;
    double ior;

    Vec3f data;
    PrimitiveType type;
    
    Primitive(Vec3f data, PrimitiveType type);

    std::optional <Intersection> intersection(const Ray &ray);
    std::optional <Intersection> intersect(const Ray &ray) const;
    std::optional <Intersection> intersectEllipsoid(const Ray &ray) const;
    std::optional <Intersection> intersectPlane(const Ray &ray) const;
    std::optional <Intersection> intersectBox(const Ray &ray) const;
};

