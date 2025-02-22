#pragma once

#include "scene.hpp"

class Renderer {
public:
    static void render(Scene& scene, const std::string& filename);
};