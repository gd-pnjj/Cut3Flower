cmake_minimum_required(VERSION 3.16)
project(Flower3D LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
endif()

# Find GLFW
find_package(glfw3 3.3 REQUIRED)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Find GLM
find_package(glm REQUIRED)

# Executable
add_executable(flower3d
    src/main.cpp
    src/application.cpp
    src/renderer.cpp
    src/camera.cpp
    src/flower.cpp
    src/shader.cpp
    src/gl_loader.cpp
)

target_include_directories(flower3d PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${GLM_INCLUDE_DIRS}
)

target_link_libraries(flower3d PRIVATE
    glfw
    ${OPENGL_LIBRARIES}
)

# Copy shaders to build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})