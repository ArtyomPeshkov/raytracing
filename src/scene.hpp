#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "camera.hpp"
#include "color.hpp"
#include "coordinate.hpp"
#include "primitive.hpp"
#include "light.hpp"

class Scene {
public:
    int width, height;
    Color bgColor;
    
    int rayDepth;
    int samples;
    Color ambient;
    Camera camera;
    
    std::vector<Primitive*> primitives;
    std::vector<Light*> lights;


    Scene() = default;

    Color raytrace(Ray ray, int bounceNum) const;
    Intersection getIntersection(Ray ray, double lower_bound) const;
};
