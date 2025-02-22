#pragma once

#include "color.hpp"
#include "camera.hpp"
#include "primitive.hpp"

#include <vector>

class Scene {
public:
    int width, height;
    Color bgColor;
    Camera camera;

    std::vector<Primitive*> primitives;

    Color raytrace(const Ray& ray);
};