#include "color.hpp"

#include <cstdint>
#include <cmath>

Color::Color(double red, double green, double blue): red(red), green(green), blue(blue) {};

std::ostream& operator<<(std::ostream& os, const Color& color) {
    uint8_t r = static_cast<uint8_t>(std::round(color.red * 255.0));
    uint8_t g = static_cast<uint8_t>(std::round(color.green * 255.0));
    uint8_t b = static_cast<uint8_t>(std::round(color.blue * 255.0));

    os << r << g << b;
    return os;
}