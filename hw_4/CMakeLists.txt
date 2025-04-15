cmake_minimum_required(VERSION 3.17)

project(hw_4)

set(CMAKE_CXX_STANDARD 17)

include_directories("../src")
file(GLOB SOURCES "../src/*.cpp")
add_executable(main ${SOURCES})
