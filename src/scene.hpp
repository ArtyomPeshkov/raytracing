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
    Color ambient;
    Camera camera;
    
    std::vector<Primitive*> primitives;
    std::vector<Light*> lights;


    Scene() = default;

    void render(std::ostream &out) const;
    Color raytrace(Ray ray, int bounceNum) const;
    Intersection getIntersection(Ray ray, float lower_bound) const;
};
