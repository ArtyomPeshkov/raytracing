#include "parser.hpp"
#include "renderer.hpp"

#include <fstream>

int main(int argc, const char *argv[]) {
    std::cout << "HW3" << std::endl;
    Scene scene = Parser::parseScene(argv[1]);
    Renderer::render(scene, argv[2]);
    return 0;
}