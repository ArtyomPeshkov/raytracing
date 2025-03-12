#pragma once

#include <iostream>
#include <cstdint>

class Color {
public:
    Color(float red = 0.0, float green = 0.0, float blue = 0.0);

    float red;
    float green;
    float blue;

    static float gamma_correction(const float &component);
    static float saturation(const float &component);
    Color tonemap() const;

    friend Color operator*(const Color& lhs, const Color& rhs);
    friend Color operator*(float scalar, const Color& color);
    friend Color operator+(const Color& color, float scalar);
    friend Color operator+(const Color& lhs, const Color& rhs);
    friend Color operator/(const Color& lhs, const Color& rhs);
    friend std::ostream& operator<<(std::ostream& os, Color color);
};
