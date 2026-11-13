cmake_minimum_required(VERSION 3.16)
project(Flower3D
    VERSION 1.1.2
    DESCRIPTION "Interactive 3D flower rendered with OpenGL"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
endif()

include(FetchContent)

# GLFW (automated, pinned to immutable release commit: 3.4)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        7b6aead9fb88b3623e3b3725ebb42670cbe4c579 # 3.4
)

# GLM (automated, header-only, pinned to immutable release commit: 1.0.3)
set(GLM_BUILD_TESTS OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        8d1fd52e5ab5590e2c81768ace50c72bae28f2ed # 1.0.3
)

FetchContent_MakeAvailable(glfw glm)

# OpenGL: system dependency (not fetched)
find_package(OpenGL REQUIRED)

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

# Generated project metadata (version)
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/version.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/generated/version.h
    @ONLY
)

target_include_directories(flower3d PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}/generated
)

target_link_libraries(flower3d PRIVATE
    glfw
    glm::glm
    OpenGL::GL
)

# Copy shaders to build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# --- Installation rules ---

# 1. Executable
install(TARGETS flower3d
    RUNTIME DESTINATION bin
)

# 2. Shaders (runtime assets)
install(DIRECTORY shaders/
    DESTINATION share/flower3d/shaders
    FILES_MATCHING PATTERN "*.vert" PATTERN "*.frag"
)

# --- CPack configuration ---
set(CPACK_PACKAGE_NAME "Flower3D")
set(CPACK_PACKAGE_VENDOR "Flower3D Maintainers")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Interactive 3D flower rendered with OpenGL")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "Flower3D-${PROJECT_VERSION}")
set(CPACK_PACKAGE_WARRANTY "Provided without warranty")
set(CPACK_PACKAGE_CONTACT "Flower3D Maintainers")
set(CPACK_PACKAGE_LICENSE "MIT")

if(WIN32)
    set(CPACK_GENERATOR "WIX;ZIP")
elseif(APPLE)
    set(CPACK_GENERATOR "productbuild;ZIP")
else()
    set(CPACK_GENERATOR "TGZ;DEB;RPM")
endif()

# --- Testing (CTest) ---
include(CTest)
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

# --- Enable CPack after install rules and tests are registered ---
include(CPack)