#pragma once

#include "scene.hpp"

class Parser {
public:
    static Scene parseScene(const std::string &filename);
    static std::string parsePrimitive(std::ifstream &input, std::vector<Primitive*> &primitives);
    static std::string parseLight(std::ifstream &input, std::vector<Light*> &lights);
};