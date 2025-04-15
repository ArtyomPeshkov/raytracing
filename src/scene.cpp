#include "scene.hpp"
#include "randomiser.hpp"

#include <string>
#include <sstream>
#include <cmath>

Intersection Scene::getIntersection(Ray ray, double limit) const {
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
        Vec3f p = ray.o + t * ray.d;
        Vec3f w = distribution->sample(p + 0.0001 * normal, normal);

        if (w * normal < 0) {
            return primitive->emission;
        }

        float pdf = distribution->pdf(p + 0.0001 * normal, normal, w);
        Ray wR = Ray(p + 0.0001 * w, w);

        auto rec_color = 1.0 / (acos(-1) * pdf) * (w * normal) * primitive->color * raytrace(wR, bounceNum - 1);
        return primitive->emission + rec_color;
    } else if (primitive->material == Material::METALLIC) {
        Vec3f reflectedDir = ray.d.normalized() - 2.0 * normal * ray.d.normalized() * normal;
        Ray reflectedRay = Ray(ray.o + t * ray.d + 0.0001 * reflectedDir, reflectedDir);

        return primitive->emission + inter_color * raytrace(reflectedRay, bounceNum - 1);
    } else {
        Vec3f reflectedDir = ray.d.normalized() - 2.0 * normal * ray.d.normalized() * normal;
        Ray reflectedRay = Ray(ray.o + t * ray.d + 0.0001 * reflectedDir, reflectedDir);
        Color reflectedColor = raytrace(reflectedRay, bounceNum - 1);

        double eta1 = (is_in ? primitive->ior : 1.0);
        double eta2 = (is_in ? 1.0 : primitive->ior);

        Vec3f l = -1.0 * ray.d.normalized();
        double sinTheta2 = (eta1 / eta2) * sqrt(1 - (normal * l) * (normal * l));

        if (fabsf(sinTheta2) > 1.0) {
            return primitive->emission + reflectedColor;
        }

        double r0 = pow((eta1 - eta2) / (eta1 + eta2), 2.0);
        double r = r0 + (1 - r0) * pow(1 - normal * l, 5.0);
        if (Random::uniform_dist_0_1(Random::rnd) < r) {
            return primitive->emission + reflectedColor;
        }

        double cosTheta2 = sqrt(1.0 - sinTheta2 * sinTheta2);
        Vec3f refractedDir = (eta1 / eta2) * (-1.0 * l) + (eta1 / eta2 * normal * l - cosTheta2) * normal;
        Ray refracted = Ray(ray.o + t * ray.d + 0.0001 * refractedDir, refractedDir);
        Color refractedColor = raytrace(refracted, bounceNum - 1);
        if (!is_in) {
            refractedColor = refractedColor * inter_color;
        }

        return primitive->emission + refractedColor;
    }
}
