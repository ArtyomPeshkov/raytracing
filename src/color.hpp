#pragma once

#include <fstream>

class Color {
public:
    Color(float red = 0, float green = 0, float blue = 0);

    float red;
    float green;
    float blue;

    friend std::ostream& operator<<(std::ostream& os, const Color& color);
};