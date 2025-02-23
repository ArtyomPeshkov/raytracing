
#include "camera.hpp"

#include <cmath>

void Camera::setupFov(float fov, float width, float height) {
    fov_x = fov;
    tan_fov_x = tan(fov_x / 2);
    tan_fov_y = tan_fov_x * height / width;
}


Ray Camera::createRay(float p_x, float p_y, float width, float height) {
    float x = (2 * (p_x + 0.5) / width - 1) * tan_fov_x;
    float y = -1.0 * (2 * (p_y + 0.5) / height - 1) * tan_fov_y;

    return {position, right * x + up * y + forward};
}