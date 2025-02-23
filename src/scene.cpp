#include "scene.hpp"

Color Scene::raytrace(const Ray& ray) {
    Color resColor = bgColor;
    float resDist = -1.0;
    for (auto &primitive : primitives) {
        auto intersection = primitive->getIntersection(ray);
        if (!intersection.has_value()) {
            continue;
        }

        if (resDist == -1.0 || intersection.value().first < resDist) {
            resDist = intersection.value().first;
            resColor = intersection.value().second;
        }
    }
    return resColor;
}