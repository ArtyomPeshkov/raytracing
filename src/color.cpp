#include "color.hpp"

#include <cmath>
#include <algorithm>

Color::Color(float red, float green, float blue) : red(red), green(green), blue(blue) {}

float Color::gamma_correction(const float &component) {
    return pow(component, 1. / 2.2);
}

float Color::saturation(const float &component) {
    return std::min(1.f, std::max(0.f, component));
}

Color Color::tonemap() const {
    const float a = 2.51f;
    const float b = 0.03f;
    const float c = 2.43f;
    const float d = 0.59f;
    const float e = 0.14f;
    return ((*this) * (a * (*this) + b)) / ((*this) * (c * (*this) + d) + e);
}

Color operator*(const Color& lhs, const Color& rhs) {
    return Color(lhs.red * rhs.red, lhs.green * rhs.green, lhs.blue * rhs.blue);
}

Color operator*(float scalar, const Color& color) {
    return Color(color.red * scalar, color.green * scalar, color.blue * scalar);
}

Color operator+(const Color& color, float scalar) {
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
    // TODO: move to function
    uint8_t r = static_cast<uint8_t>(std::round(Color::gamma_correction(Color::saturation(toned.red)) * 255.0));
    uint8_t g = static_cast<uint8_t>(std::round(Color::gamma_correction(Color::saturation(toned.green)) * 255.0));
    uint8_t b = static_cast<uint8_t>(std::round(Color::gamma_correction(Color::saturation(toned.blue)) * 255.0));

    os << r << g << b;
    return os;
}
