#include <cmath>
#include "light.hpp"

LightResult Light::getLight(Vec3f point) const {
    if (type == LightType::Dot) {
        Vec3f direction = position - point;
        float length = std::sqrt(direction.self_dot());
        Color resulting = 1.0 / (attenuation.x + attenuation.y * length + attenuation.z * length * length) * intensity;
        return LightResult{direction.normalized(), resulting, length};
    } else if (type == LightType::Direction) {
        return LightResult{direction.normalized(), intensity, 1. / 0.001};
    } else {
        // std::cout << "Unexpected"
    }
}
