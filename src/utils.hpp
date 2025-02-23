#pragma once

#include <optional>
#include <cmath>

std::pair<double, double> solveEq(double a, double b, double c) {
    double d = b * b - 4 * a * c;
    if (d <= 0) {
        return {};
    }

    double x1 = (-b - sqrt(d)) / (2 * a);
    double x2 = (-b + sqrt(d)) / (2 * a);
    return {x1, x2};
}

std::optional<double> getCorrectRoot(std::pair<double, double> roots) {
    double ans = std::min(std::max(0., roots.first), std::max(0., roots.second));
    // TODO: check
    if (ans > 0) {
        return ans;
    }
    return {};
}