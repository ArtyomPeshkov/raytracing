#include "scene.hpp"

Color Scene::raytrace(const Ray& ray) {
    Color resColor = bgColor;
    double resDist = -1;
    for (auto &primitive : primitives) {
        auto intersection = primitive->getIntersection(ray);
        if (!intersection.has_value()) {
            continue;
        }

        if (resDist == -1 || intersection.value().first < resDist) {
            resDist = intersection.value().first;
            resColor = intersection.value().second;
        }
    }
    return resColor;
}