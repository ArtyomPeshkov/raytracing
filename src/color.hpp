#pragma once

#include <iostream>
#include <cstdint>

class Color {
public:
    Color(double red = 0.0, double green = 0.0, double blue = 0.0);

    double red;
    double green;
    double blue;

    static double gamma_correction(const double &component);
    static double saturation(const double &component);
    Color tonemap() const;

    friend Color operator*(const Color& lhs, const Color& rhs);
    friend Color operator*(double scalar, const Color& color);
    friend Color operator+(const Color& color, double scalar);
    friend Color operator+(const Color& lhs, const Color& rhs);
    friend Color operator/(const Color& lhs, const Color& rhs);
    friend std::ostream& operator<<(std::ostream& os, Color color);
};
