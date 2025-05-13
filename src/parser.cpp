#include "parser.hpp"
#include "distribution.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

std::string Parser::parsePrimitive(std::ifstream &input, std::vector<Primitive*> &primitives) {
    std::string primitiveType;
    Primitive* primitive;

    std::string line;
    std::getline(input, line);
    std::istringstream iss(line);
    iss >> primitiveType;

    double d_x, d_y, d_z;
    iss >> d_x >> d_y >> d_z;
    if (primitiveType == "ELLIPSOID") {
        primitive = new Primitive({d_x, d_y, d_z}, PrimitiveType::ELLIPSOID);
    } else if (primitiveType == "PLANE") {
        primitive = new Primitive({d_x, d_y, d_z}, PrimitiveType::PLANE);
    } else if (primitiveType == "BOX") {
        primitive = new Primitive({d_x, d_y, d_z}, PrimitiveType::BOX);
    } else {
        std::cout << "Unknown primitive: " << primitiveType << std::endl;
        return "";
    }


    while (std::getline(input, line)) {
        std::string property;
        std::istringstream iss(line);
        iss >> property;

        if (property == "COLOR") {
            double r, g, b;
            iss >> r >> g >> b;
            primitive->color = {r, g, b};
        } else if (property == "POSITION") {
            double x, y, z;
            iss >> x >> y >> z;
            primitive->position = {x, y, z};
        } else if (property == "ROTATION") {
            double x, y, z, w;
            iss >> x >> y >> z >> w;
            primitive->rotation = {x, y, z, w};
        } else if (property == "METALLIC") {
            primitive->material = Material::METALLIC;
        } else if (property == "DIELECTRIC") {
            primitive->material = Material::DIELECTRIC;
        } else if (property == "IOR") {
            iss >> primitive->ior;
        } else if (property == "EMISSION") {
            float r, g, b;
            iss >> r >> g >> b;

            primitive->emission = Color(r, g, b);

        } else {
            primitives.push_back(primitive);
            return line;
        }
    }

    primitives.push_back(primitive);
    return "";
}

Scene Parser::parseScene(const std::string &filename) {
    Scene scene{};
    std::ifstream file(filename);
    std::string line = "";

    while (true) {
        if (line == "") {
            if (!std::getline(file, line)) {
                break;
            }
        }

        std::istringstream iss(line);
        std::string property;
        iss >> property;

        if (property == "DIMENSIONS") {
            iss >> scene.width >> scene.height;
        } else if (property == "BG_COLOR") {
            double r, g, b;
            iss >> r >> g >> b;
            scene.bgColor = {r, g, b};
        } else if (property == "CAMERA_POSITION") {
            double x, y, z;
            iss >> x >> y >> z;
            scene.camera.position = {x, y, z};
        } else if (property == "CAMERA_RIGHT") {
            double x, y, z;
            iss >> x >> y >> z;
            scene.camera.right = {x, y, z};
        } else if (property == "CAMERA_UP") {
            double x, y, z;
            iss >> x >> y >> z;
            scene.camera.up = {x, y, z};
        } else if (property == "CAMERA_FORWARD") {
            double x, y, z;
            iss >> x >> y >> z;
            scene.camera.forward = {x, y, z};
        } else if (property == "CAMERA_FOV_X") {
            double fov_x;
            iss >> fov_x;
            scene.camera.setupFov(fov_x, scene.width, scene.height);
        } else if (property == "RAY_DEPTH") {
            iss >> scene.rayDepth;
        } else if (property == "AMBIENT_LIGHT") {
            double r, g, b;
            iss >> r >> g >> b;
            scene.ambient = {r, g, b};
        } else if (property == "SAMPLES") {
            iss >> scene.samples;
        } else if (property == "NEW_PRIMITIVE") {
            line = parsePrimitive(file, scene.primitives);
            continue;
        } else if (property == "NEW_LIGHT") {
            // line = parseLight(file, scene.lights);
            continue;
        } else {
            std::cout << "Ignored line: " << line << std::endl;
        }
        line = "";
    }

    std::vector<Distribution*> lights;
    for (auto primitive: scene.primitives) {
        if ((primitive->emission.red > 0 || primitive->emission.green > 0 || primitive->emission.blue > 0) && primitive->type != PrimitiveType::PLANE) {
            lights.push_back(new Light(*primitive));
        }
    }

    std::vector<Distribution*> mix;
    mix.push_back(new Cosine());
    if (!lights.empty()) {
        mix.push_back(new Mix(lights));
    }
    scene.distribution = new Mix(mix);

    return scene;
}
