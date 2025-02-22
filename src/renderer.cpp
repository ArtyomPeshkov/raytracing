#include "renderer.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

void Renderer::render(Scene& scene, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);

    file << "P6\n";
    file << scene.width << " " << scene.height << '\n';
    file << "255\n";
    for (int y = 0; y < scene.height; y++) {
        for (int x = 0; x < scene.width; x++) {
            file << scene.raytrace(scene.camera.createRay(x, y, scene.width, scene.height));
        }
    }
}
