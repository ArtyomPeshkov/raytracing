#pragma once

#include <optional>
#include <cmath>

std::pair<float, float> solveEq(float a, float b, float c) {
    float d = b * b - 4 * a * c;
    if (d <= 0.0) {
        return {};
    }

    float x1 = (-b - sqrt(d)) / (2 * a);
    float x2 = (-b + sqrt(d)) / (2 * a);
    return {x1, x2};
}

std::optional<float> getCorrectRoot(std::pair<float, float> roots) {
    float ans = std::min(std::max(0.f, roots.first), std::max(0.f, roots.second));
    // TODO: check
    if (ans > 0.0) {
        return ans;
    }
    return {};
}