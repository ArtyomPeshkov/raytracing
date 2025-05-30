
#include "camera.hpp"

#include <cmath>

void Camera::setupFov(double fov, double width, double height) {
    fov_x = fov;
    tan_fov_x = tan(fov_x / 2);
    tan_fov_y = tan_fov_x * height / width;
}


Ray Camera::createRay(double p_x, double p_y, double width, double height) const{
    double x = (2.0 * (p_x + 0.5) / width - 1.0) * tan_fov_x;
    double y = -1.0 * (2.0 * (p_y + 0.5) / height - 1.0) * tan_fov_y;
    return {position, x * right + y * up + forward};
}
