cmake_minimum_required(VERSION 3.2)

include(../simplicity/simplicity-common.cmake)

# Project
project(simplicity-opengl)

# Paths
file(GLOB_RECURSE SRC_FILES src/main/c++/*.cpp src/main/c++/*.h)
include_directories(../simplicity/src/main/c++)
include_directories(dep/freeimageplus/include)
include_directories(dep/glew/include)
include_directories(src/main/c++)

# Output
add_library(simplicity-opengl STATIC ${SRC_FILES})
