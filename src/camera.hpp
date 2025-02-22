#pragma once

#include "coordinate.hpp"
#include "ray.hpp"

class Camera {
public:
    Vec3f position;

    Vec3f right;
    Vec3f up;
    Vec3f forward;

    float fov_x;

    float tan_fov_x;
    float tan_fov_y;

    void setupFov(float fov_x, float width, float height);
    Ray createRay(float x, float y, float width, float height);
};
