#pragma once

#include "coordinate.hpp"
#include "quaternion.hpp"
#include "color.hpp"
#include "ray.hpp"

#include <optional>

class Primitive {
public:
    // TODO: use std::variant<plane, box, ellipse> instead and std::visit for intersect
    Vec3f position = Vec3f();
    Quaternion rotation = Quaternion();
    Color color = Color();

    std::optional<std::pair<float, Color>> getIntersection(const Ray &ray);
    virtual std::optional<float> intersection(const Ray &ray) const {};
};

class Ellipsoid : public Primitive {
public:
    Ellipsoid(Vec3f r);

    Vec3f radius;

    std::optional<float> intersection(const Ray &ray) const override;
};

class Plane : public Primitive {
public:
    Plane(Vec3f n);

    Vec3f normal;

    std::optional<float> intersection(const Ray &ray) const override;
};

class Box : public Primitive {
public:
    Box(Vec3f s);
    
    Vec3f size;

    std::optional<float> intersection(const Ray &ray) const override;
    
};