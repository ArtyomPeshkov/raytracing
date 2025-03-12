#pragma once

#include <optional>
#include "coordinate.hpp"
#include "color.hpp"
#include "quaternion.hpp"
#include "ray.hpp"

enum class Material {
    DIFFUSE, METALLIC, DIELECTRIC
};

struct Intersection {
    Intersection(float t = 0, bool is_in = false, Vec3f normal = Vec3f(0, 0, 0), Color color = Color(0, 0, 0), int index = -1): t(t), normal(normal), color(color), is_in(is_in), primitiveIndex(index) {};

    Vec3f normal;
    bool is_in;
    float t;
    Color color;
    int primitiveIndex;
};

class Primitive {
public:
    Vec3f position{};
    Quaternion rotation = {0, 0, 0, 1};
    Color color;

    Material material = Material::DIFFUSE;
    float ior;

    Primitive() = default;

    std::optional <Intersection> intersection(const Ray &ray);
    virtual std::optional <Intersection> intersect(const Ray &ray) const = 0;
};

class Plane : public Primitive {
public:
    Vec3f normal{};

    Plane(Vec3f n);
    Plane() = default;

    std::optional <Intersection> intersect(const Ray &ray) const override;
};

class Ellipsoid : public Primitive {
public:
    Vec3f radius{};

    Ellipsoid(Vec3f r);
    Ellipsoid() = default;

    std::optional <Intersection> intersect(const Ray &ray) const override;
};

class Box : public Primitive {
public:
    Vec3f size{};

    Box(Vec3f s);
    Box() = default;

    std::optional <Intersection> intersect(const Ray &ray) const override;
};
