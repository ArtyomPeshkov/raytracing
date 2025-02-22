#include "color.hpp"

Color::Color(float red, float green, float blue): red(red), green(green), blue(blue) {};

std::ostream& operator<<(std::ostream& os, const Color& color) {
    uint8_t r = static_cast<uint8_t>(color.red * 255);
    uint8_t g = static_cast<uint8_t>(color.green * 255);
    uint8_t b = static_cast<uint8_t>(color.blue * 255);

    os << r << g << b;
    return os;
}