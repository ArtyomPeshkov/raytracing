#pragma once

#include <fstream>

class Color {
public:
    Color(double red = 0.0, double green = 0.0, double blue = 0.0);

    double red;
    double green;
    double blue;

    friend std::ostream& operator<<(std::ostream& os, const Color& color);
};