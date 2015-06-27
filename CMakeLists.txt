cmake_minimum_required(VERSION 3.2)

include(../simplicity/simplicity-common.cmake)

# Project
#########################
project(simplicity-opengl)

# Project Dependencies
#########################

# Free Image Plus
set(FREEIMAGEPLUS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/FreeImage3170/Dist/libfreeimageplus.a)
add_custom_command(
	OUTPUT ${FREEIMAGEPLUS_PATH}
	COMMAND make -f Makefile.fip
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib/FreeImage3170
	COMMENT "Building Free Image Plus")
add_custom_target(freeImagePlus DEPENDS ${FREEIMAGEPLUS_PATH})

# GLEW
set(GLEW_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/glew/lib/libGLEW.a)
set(GLEW32_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/glew/lib/glew32.lib)
add_custom_command(
	OUTPUT ${GLEW_PATH}
	COMMAND make extensions
	COMMAND make
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib/glew
	COMMENT "Building GL Extension Wrangler")
add_custom_target(glew DEPENDS ${GLEW_PATH})

# Source
#########################
file(GLOB_RECURSE SRC_FILES src/main/c++/*.cpp src/main/c++/*.h)

# Target
#########################
add_library(simplicity-opengl STATIC ${SRC_FILES})
target_include_directories(simplicity-opengl PUBLIC src/main/c++)

# Target Dependencies
#########################

# Free Image Plus
add_dependencies(simplicity-opengl freeImagePlus)
target_include_directories(simplicity-opengl PUBLIC lib/FreeImage3170/Dist)
target_link_libraries(simplicity-opengl ${FREEIMAGEPLUS_PATH})

# GLEW
add_dependencies(simplicity-opengl glew)
target_include_directories(simplicity-opengl PUBLIC lib/glew/include)
IF(WIN32)
    target_link_libraries(simplicity-opengl ${GLEW32_PATH})
ENDIF(WIN32)
IF(UNIX)
	target_link_libraries(simplicity-opengl ${GLEW_PATH})
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
