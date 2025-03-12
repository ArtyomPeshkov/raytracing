#include "parser.hpp"

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

    if (primitiveType == "ELLIPSOID") {
        double r_x, r_y, r_z;
        iss >> r_x >> r_y >> r_z;
        primitive = new Ellipsoid({r_x, r_y, r_z});
    } else if (primitiveType == "PLANE") {
        double n_x, n_y, n_z;
        iss >> n_x >> n_y >> n_z;
        primitive = new Plane({n_x, n_y, n_z});
    } else if (primitiveType == "BOX") {
        double e_x, e_y, e_z;
        iss >> e_x >> e_y >> e_z;
        primitive = new Box({e_x, e_y, e_z});
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
        } else {
            primitives.push_back(primitive);
            return line;
        }
    }

    primitives.push_back(primitive);
    return "";
}

std::string Parser::parseLight(std::ifstream &input, std::vector<Light*> &lights) {
    Light* res = new Light();
    
    res->type = LightType::Dot;

    std::string line;
    while (std::getline(input, line)) {
        std::string property;
        std::istringstream iss(line);
        iss >> property;

        if (property == "LIGHT_INTENSITY") {
            double r, g, b;
            iss >> r >> g >> b;
            res->intensity = {r, g, b};
        } else if (property == "LIGHT_POSITION") {
            double x, y, z;
            iss >> x >> y >> z;
            res->position = {x, y, z};
        } else if (property == "LIGHT_DIRECTION") {
            double x, y, z;
            iss >> x >> y >> z;
            res->direction = {x, y, z};
            res->type = LightType::Direction;
        } else if (property == "LIGHT_ATTENUATION") {
            double x, y, z;
            iss >> x >> y >> z;
            res->attenuation = {x, y, z};
        } else {
            lights.push_back(res);
            return line;
        }
    }

    lights.push_back(res);
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
        } else if (property == "NEW_PRIMITIVE") {
            line = parsePrimitive(file, scene.primitives);
            continue;
        } else if (property == "NEW_LIGHT") {
            line = parseLight(file, scene.lights);
            continue;
        } else {
            std::cout << "Ignored line: " << line << std::endl;
        }
        line = "";
    }

    return scene;
}
