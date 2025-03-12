#include "scene.hpp"

#include <string>
#include <sstream>
#include <cmath>

Intersection Scene::getIntersection(Ray ray, float limit) const {
    Intersection result;
    result.color = bgColor;
    for (int i = 0; i < primitives.size(); i++) {
        auto intersection = primitives[i]->intersection(ray);
        if (intersection.has_value() && intersection.value().t <= limit && (result.primitiveIndex == -1 || intersection.value().t < result.t)) {
            intersection.value().primitiveIndex = i;
            result = intersection.value();
        }
    }
    return result;
}

Color Scene::raytrace(Ray ray, int bounceNum) const {
    if (bounceNum == 0) {
        return {0.0, 0.0, 0.0};
    }

    auto intersection = getIntersection(ray,  1e9);
    if (intersection.primitiveIndex == -1) {
        return bgColor;
    }

    auto [normal, is_in, t, inter_color, index] = intersection;
    auto primitive = primitives[index];

    if (primitive->material == Material::DIFFUSE) {
        Color default_color = ambient;
        for (const auto &lightSource : lights) {
            Vec3f ray_point = ray.o + t * ray.d;

            auto [l, color, limit] = lightSource->getLight(ray_point);
            float reflected = l * normal;
            if (reflected >= 0 && getIntersection(Ray(ray_point + 0.0001 * l, l), limit).primitiveIndex == -1) {
                default_color = default_color + reflected * color;
            }
        }
        return default_color * inter_color;
    } else if (primitive->material == Material::METALLIC) {
        Vec3f reflectedDir = ray.d.normalized() - 2.0 * normal * ray.d.normalized() * normal;
        Ray reflectedRay = Ray(ray.o + t * ray.d + 0.0001 * reflectedDir, reflectedDir);
        return inter_color * raytrace(reflectedRay, bounceNum - 1);
    } else {
        Vec3f reflectedDir = ray.d.normalized() - 2.0 * normal * ray.d.normalized() * normal;
        Ray reflectedRay = Ray(ray.o + t * ray.d + 0.0001 * reflectedDir, reflectedDir);
        Color reflectedColor = raytrace(reflectedRay, bounceNum - 1);

        float eta1 = (is_in ? primitive->ior : 1.0);
        float eta2 = (is_in ? 1.0 : primitive->ior);

        Vec3f l = -1.0 * ray.d.normalized();
        float sinTheta2 = (eta1 / eta2) * sqrt(1 - (normal * l) * (normal * l));

        if (fabsf(sinTheta2) > 1.0) {
            return reflectedColor;
        }

        float cosTheta2 = sqrt(1 - sinTheta2 * sinTheta2);
        Vec3f refractedDir = (eta1 / eta2) * (-1.0 * l) + (eta1 / eta2 * normal * l - cosTheta2) * normal;
        Ray refracted = Ray(ray.o + t * ray.d + 0.0001 * refractedDir, refractedDir);
        Color refractedColor = raytrace(refracted, bounceNum - 1);
        if (!is_in) {
            refractedColor = refractedColor * inter_color;
        }

        float r0 = pow((eta1 - eta2) / (eta1 + eta2), 2.0);
        float r = r0 + (1 - r0) * pow(1 - normal * l, 5.0);
        return r * reflectedColor + (1 - r) * refractedColor;
    }
}

void Scene::render(std::ostream &out) const {
    out << "P6\n";
    out << width << " " << height << '\n';
    out << 255 << '\n';
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            float tan_x = std::tan(camera.fov_x / 2);
            float tan_y = tan_x * float(height) / float(width);

            float cx = 2.0 * (x + 0.5) / width - 1.0;
            float cy = 2.0 * (y + 0.5) / height - 1.0;

            float real_x = tan_x * cx;
            float real_y = tan_y * cy;

            Ray real_ray = Ray(camera.position, real_x * camera.right - real_y * camera.up + camera.forward);

            auto pixel = raytrace(real_ray, rayDepth);

            out << pixel;
        }
    }
}
