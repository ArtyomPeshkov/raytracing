cmake_minimum_required(VERSION 3.17)

project(hw_3)

include_directories("../src")
file(GLOB SOURCES "../src/*.cpp")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(main ${SOURCES})
