#include "color.hpp"

#include <cmath>
#include <algorithm>

Color::Color(double red, double green, double blue) : red(red), green(green), blue(blue) {}

double Color::gamma_correction(const double &component) {
    return pow(component, 1. / 2.2);
}

double Color::saturation(const double &component) {
    return std::min(1.0, std::max(0.0, component));
}

Color Color::tonemap() const {
    const double a = 2.51f;
    const double b = 0.03f;
    const double c = 2.43f;
    const double d = 0.59f;
    const double e = 0.14f;
    return ((*this) * (a * (*this) + b)) / ((*this) * (c * (*this) + d) + e);
}

Color operator*(const Color& lhs, const Color& rhs) {
    return Color(lhs.red * rhs.red, lhs.green * rhs.green, lhs.blue * rhs.blue);
}

Color operator*(double scalar, const Color& color) {
    return Color(color.red * scalar, color.green * scalar, color.blue * scalar);
}

Color operator+(const Color& color, double scalar) {
    return Color(color.red + scalar, color.green + scalar, color.blue + scalar);
}

Color operator+(const Color& lhs, const Color& rhs) {
    return Color(lhs.red + rhs.red, lhs.green + rhs.green, lhs.blue + rhs.blue);
}

Color operator/(const Color& lhs, const Color& rhs) {
    return Color(lhs.red / rhs.red, lhs.green / rhs.green, lhs.blue / rhs.blue);
}

std::ostream& operator<<(std::ostream& os, Color color) {
    Color toned = color.tonemap();

    uint8_t r = static_cast<uint8_t>(std::round(Color::gamma_correction(Color::saturation(toned.red)) * 255.0));
    uint8_t g = static_cast<uint8_t>(std::round(Color::gamma_correction(Color::saturation(toned.green)) * 255.0));
    uint8_t b = static_cast<uint8_t>(std::round(Color::gamma_correction(Color::saturation(toned.blue)) * 255.0));

    os << r << g << b;
    return os;
}
