cmake_minimum_required(VERSION 2.8)

include(../../simplicity/simplicity/simplicity-common.cmake)

# Project
project(simplicity-opengl)

# Policies
cmake_policy(SET CMP0015 NEW)

# Paths
file(GLOB_RECURSE SRC_FILES src/main/c++/*.cpp src/main/c++/*.h)
include_directories(../../simplicity/simplicity/src/main/c++)
include_directories(dep/freeimageplus/include)
include_directories(dep/glew/include)
include_directories(src/main/c++)

link_directories(dep/freeimageplus/lib)
link_directories(dep/glew/lib)

# Output
add_library(simplicity-opengl STATIC ${SRC_FILES})

target_link_libraries(simplicity-opengl freeimageplus)
target_link_libraries(simplicity-opengl freeimage)
IF(WIN32)
	target_link_libraries(simplicity-opengl glew32)
	target_link_libraries(simplicity-opengl GlU32)
	target_link_libraries(simplicity-opengl OpenGL32)
ENDIF(WIN32)
IF(UNIX)
	target_link_libraries(simplicity-opengl GLEW)
	target_link_libraries(simplicity-opengl GLU)
	target_link_libraries(simplicity-opengl GL)
ENDIF(UNIX)

