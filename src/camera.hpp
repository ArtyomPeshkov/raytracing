#pragma once

#include "coordinate.hpp"
#include "ray.hpp"

class Camera {
public:
    Vec3f position;

    Vec3f right;
    Vec3f up;
    Vec3f forward;

    double fov_x;

    double tan_fov_x;
    double tan_fov_y;

    void setupFov(double fov_x, double width, double height);
    Ray createRay(double x, double y, double width, double height) const;
};
