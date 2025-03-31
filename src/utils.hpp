#pragma once

#include "primitive.hpp"

#include <optional>
#include <cmath>

double sign(double val) {
    if (val < 0.0) {
        return -1.0;
    } else {
        return 1.0;
    }
}

std::optional<std::pair<double, double>> solveEq(double a, double b, double c) {
    double d = b * b - 4 * a * c;
    if (d <= 0.0) {
        return {};
    }

    double x1 = (-b - sqrt(d)) / (2 * a);
    double x2 = (-b + sqrt(d)) / (2 * a);
    return { {x1, x2} };
}

std::optional<Intersection> getCorrectRoot(std::optional<std::pair<double, double>> opt_roots) {
    if (!opt_roots.has_value()) {
        return {};
    }
    
    std::pair<double, double> roots = opt_roots.value();
    double x1 = std::min(roots.first, roots.second);
    double x2 = std::max(roots.first, roots.second);

    if (x2 <= 0) {
        return {};
    } else if (x1 <= 0) {
        return Intersection(x2, true);
    }
    return Intersection(x1, false);
}