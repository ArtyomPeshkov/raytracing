#pragma once

#include <tuple>
#include "color.hpp"
#include "coordinate.hpp"

enum LightType {
    Direction,
    Dot
};

struct LightResult {
    Vec3f point{};
    Color color{};
    float r{};
};

class Light {
public:
    LightType type;
    Color intensity;
    Vec3f position;
    Vec3f attenuation;
    Vec3f direction;

    LightResult getLight(Vec3f point) const;

    Light() = default;
};

