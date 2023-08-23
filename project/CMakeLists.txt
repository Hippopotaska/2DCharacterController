# Specify minimum supported cmake version
cmake_minimum_required(VERSION 3.2)
project(2DCharacterController)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)

add_subdirectory("dependencies/glfw-3.3.8")
add_compile_definitions(GLEW_STATIC)

# Include all files
file(GLOB_RECURSE 2DCharacterController_SRC
	"src/*.h"
	"src/*.cpp"
	"src/*.shader"
)

# GLEW source
set(GLEW_SRC
    "dependencies/include/GL/wglew.h"
    "dependencies/include/GL/glew.h"
    "dependencies/src/glew.c"
)
source_group("OpenGL/Glew" FILES ${GLEW_SRC})
list(APPEND 2DCharacterController_SRC ${GLEW_SRC})

# Find OpenGL
find_package(OpenGL REQUIRED)

# Add executable files
add_executable(2DCharacterController ${2DCharacterController_SRC})
target_link_libraries(2DCharacterController OpenGL::GL glfw)
#target_link_libraries(2DCharacterController OpenGL::GL ImGUI)

# Include directories
include_directories("src")
include_directories("dependencies/include")
include_directories("dependencies/glfw-3.3.8/include")
include_directories("dependencies/glm-0.9.9.8")

# Set 2DCharacterController as startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT 2DCharacterController)

# Setting main directory 
set_target_properties(2DCharacterController PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
                                              VS_DEBUGGER_COMMAND           "$<TARGET_FILE:2DCharacterController>"
                                              VS_DEBUGGER_ENVIRONMENT       "PATH=%PATH%;${CMAKE_PREFIX_PATH}/bin")