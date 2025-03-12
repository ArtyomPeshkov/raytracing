#pragma once

#include "primitive.hpp"

#include <optional>
#include <cmath>

std::optional<std::pair<float, float>> solveEq(float a, float b, float c) {
    float d = b * b - 4 * a * c;
    if (d <= 0.0) {
        return {};
    }

    float x1 = (-b - sqrt(d)) / (2 * a);
    float x2 = (-b + sqrt(d)) / (2 * a);
    return { {x1, x2} };
}

std::optional<Intersection> getCorrectRoot(std::optional<std::pair<float, float>> opt_roots) {
    if (!opt_roots.has_value()) {
        return {};
    }
    
    std::pair<float, float> roots = opt_roots.value();
    float x1 = std::min(roots.first, roots.second);
    float x2 = std::max(roots.first, roots.second);

    if (x2 <= 0) {
        return {};
    } else if (x1 <= 0) {
        return Intersection(x2, true);
    }
    return Intersection(x1, false);
}