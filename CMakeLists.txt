cmake_minimum_required(VERSION 3.2)

include(../simplicity/simplicity-common.cmake)

# Project
#########################
project(simplicity-opengl)

# Source
#########################
file(GLOB_RECURSE SRC_FILES src/main/c++/*.cpp src/main/c++/*.h)

# Target
#########################
add_library(simplicity-opengl STATIC ${SRC_FILES})
target_include_directories(simplicity-opengl PUBLIC src/main/c++)

# Target Dependencies
#########################

# FreeImagePlus
target_include_directories(simplicity-opengl PUBLIC dep/freeimageplus/include)
target_link_libraries(simplicity-opengl freeimageplus)
target_link_libraries(simplicity-opengl freeimage)

# GLEW
target_include_directories(simplicity-opengl PUBLIC dep/glew/include)
IF(WIN32)
    target_link_libraries(simplicity-opengl glew32)
ENDIF(WIN32)
IF(UNIX)
	target_link_libraries(simplicity-opengl GLEW)
ENDIF(UNIX)

# OpenGL
IF(WIN32)
	target_link_libraries(simplicity-opengl GlU32)
	target_link_libraries(simplicity-opengl OpenGL32)
ENDIF(WIN32)
IF(UNIX)
	target_link_libraries(simplicity-opengl GLU)
	target_link_libraries(simplicity-opengl GL)
ENDIF(UNIX)

# Simplicity
target_link_libraries(simplicity-opengl simplicity)
