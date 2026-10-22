# 3D Flower

A lightweight desktop application rendering an interactive, rotating 3D flower in a real-time window.

## Graphics & Rendering

* Use OpenGL for 3D rendering.
* Target a stable 60 FPS update and render loop.
* Implement basic Phong lighting (ambient, diffuse, specular).
* Support smooth continuous rotation along the Y-axis only.

## Controls & Windowing

* Use GLFW for cross-platform window management.
* Allow basic mouse interaction for camera orbit and zoom.
* Handle window resizing dynamically without aspect ratio distortion.

## Code Style

* Use C++ for ALL new files.
* Avoid Glad for building the project
* Use 2 spaces for indentation.
* Prefer modern C++ (C++17 or newer).
* Use RAII for GPU resource management (VBO, VAO, shaders).

## Architecture

* Keep functions under 200 lines.
* Use dependency injection.
* Separate rendering logic from application state.

## Testing

* Write unit tests for all business logic.
* Maintain >80% code coverage.
* Use Catch2 for C++ unit testing.

## Security

* NEVER commit API keys or secrets.
* Validate ALL user inputs/.
* Sanitize file paths when loading external assets (shaders, models, textures).

## Current state of the project

* Implemented: GLFW window, OpenGL 3.3 core rendering, 3D flower geometry, Phong lighting, camera orbit/zoom, resize handling.
* Controls: left-drag orbit, Shift+left-drag orbit around current view target, scroll zoom, Esc to quit.
* Build: CMake with glfw3/OpenGL/glm; run from project root so `shaders/` resolve.