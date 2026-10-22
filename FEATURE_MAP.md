# Feature Map

## Windowing & App Lifecycle
- Files: `src/main.cpp`, `src/application.cpp`, `include/application.h`
- Customization: window size/title defaults (800x600, "3D Flower"); ESC closes; resize callback updates viewport/aspect.

## OpenGL Loading
- Files: `src/gl_loader.cpp`, `include/gl_loader.h`
- Customization: minimal native loader via `glfwGetProcAddress` (no GLAD); loads GL 3.3 core functions.

## Rendering Pipeline
- Files: `src/renderer.cpp`, `include/renderer.h`, `src/shader.cpp`, `include/shader.h`
- Customization: VAO/VBO/EBO setup; Phong uniforms (light/material/viewPos); model/view/projection matrices.

## Camera
- Files: `src/camera.cpp`, `include/camera.h`
- Customization: FOV 45, aspect, near/far; mouse sensitivity 0.1; scroll sensitivity 1.0; orbit around current target on Shift.

## Flower Geometry
- Files: `src/flower.cpp`, `include/flower.h`
- Customization: petal count 8, segments 16, length 1.0, width 0.5; center + stem generation.

## Shaders
- Files: `shaders/flower.vert`, `shaders/flower.frag`
- Customization: Phong lighting (ambient/diffuse/specular), model/view/projection transforms.

## Build
- Files: `CMakeLists.txt`
- Customization: C++17, warnings, links glfw/OpenGL, copies shaders to build dir.
