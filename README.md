# 3D Flower

Lightweight desktop app rendering an interactive rotating 3D flower with OpenGL.

## Build
```bash
cmake -S . -B build
cmake --build build
```

## Run
```bash
./build/flower3d
```
Run from the project root so `shaders/` resolve.

## Controls
- Left drag: orbit camera
- Shift + left drag: orbit around current view target
- Scroll: zoom
- Arrow keys: unused (removed)
- Esc: quit

## Dependencies
- GLFW 3.3+
- OpenGL
- GLM
