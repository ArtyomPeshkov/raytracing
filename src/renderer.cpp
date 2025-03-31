#include "renderer.hpp"
#include "randomiser.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <mutex>

void Renderer::render(Scene& scene, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);

    file << "P6\n";
    file << scene.width << " " << scene.height << '\n';
    file << 255 << '\n';

    int num_threads = std::min(scene.samples, (int)std::thread::hardware_concurrency());
    int work_per_thread = scene.samples / num_threads;

    for (int y = 0; y < scene.height; y++) {
        for (int x = 0; x < scene.width; x++) {
            std::vector <std::thread> threads;
            std::mutex lock;

            Color final_color = Color();
            for (int i = 0; i < scene.samples; i+=work_per_thread) {
                threads.emplace_back([&, i]{
                    Color partial_color;
                    for (int j = i; j < std::min(i + work_per_thread, scene.samples); j++) {
                        double x_off = x + Random::uniform_dist_0_1(Random::rnd);
                        double y_off = y + Random::uniform_dist_0_1(Random::rnd);

                        Ray ray = scene.camera.createRay(x_off, y_off, scene.width, scene.height);
                        partial_color = partial_color + scene.raytrace(ray, scene.rayDepth);
                    }

                    lock.lock();
                    final_color = final_color + partial_color;
                    lock.unlock();
                });
            }
            for (auto& t : threads)
                t.join();

            file << ((1.0 / scene.samples) * final_color);
        }
    }
}
