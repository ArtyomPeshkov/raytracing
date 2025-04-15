#pragma once

#include <random>
#include "randomiser.hpp"
#include "coordinate.hpp"
#include "primitive.hpp"

class Distribution {
public:
    virtual Vec3f sample(Vec3f x, Vec3f n) = 0;
    virtual double pdf(Vec3f x, Vec3f n, Vec3f d) = 0;
};

class Cosine : public Distribution {
public:
    explicit Cosine() {}

    Vec3f sample(Vec3f x, Vec3f n) override;
    double pdf(Vec3f x, Vec3f n, Vec3f d) override;
};

class Light : public Distribution {
public:
    Primitive &primitive;
    explicit Light(Primitive &primitive): primitive(primitive) {}

    double pdf(Vec3f x, Vec3f n, Vec3f d) override;

    double getPDF(Vec3f x, Vec3f d, Vec3f y, Vec3f yn);
    double boxgetPDF(Vec3f x, Vec3f d, Vec3f y, Vec3f yn);
    double ellipsoidgetPDF(Vec3f x, Vec3f d, Vec3f y, Vec3f yn);

    Vec3f sample(Vec3f x, Vec3f n) override;
    Vec3f boxSample(Vec3f x, Vec3f n);
    Vec3f ellipsoidSample(Vec3f x, Vec3f n);
};

class Mix : public Distribution {
public:
    std::vector<Distribution*> components;

    Mix(std::vector<Distribution*> &&components): components(std::move(components)) {}

    Vec3f sample(Vec3f x, Vec3f n) override;
    double pdf(Vec3f x, Vec3f n, Vec3f d) override;
};