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
        } else if (property == "NEW_PRIMITIVE") {
            line = parsePrimitive(file, scene.primitives);
            continue;
        } else {
            std::cout << "Ignored line: " << line << std::endl;
        }
        line = "";
    }

    return scene;
}
