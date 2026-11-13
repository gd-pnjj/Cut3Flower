# 3D Flower

Lightweight desktop app rendering an interactive rotating 3D flower with OpenGL.

## Project version

- **Current version:** `1.1.2`
- **Versioning convention:** [Semantic Versioning](https://semver.org/) (`MAJOR.MINOR.PATCH`)
  - `1.0.0` — initial release
  - `1.1.0` — minor update (added `quick_test.py`)
  - `1.1.2` — patch updates (current CMake/build-system work and the preceding patch commit)
- **Canonical source:** the version is defined once in the root `CMakeLists.txt` (`project(Flower3D VERSION 1.1.2 ...)`) and reused from `${PROJECT_VERSION}` (e.g. generated C++ metadata in `build/generated/version.h`). Avoid duplicating the version string elsewhere.
- **Git tags:** no version tags are currently present in this repository. If releases are tagged later, use the form `vMAJOR.MINOR.PATCH` (e.g. `v1.1.2`) corresponding to the CMake project version. Do not create or push tags without explicit authorization.

## Dependencies

Three dependencies are required to build and run the application:

1. **GLFW** — windowing, input, and OpenGL context management.
   Version 3.4.
   *Source: fetched automatically by CMake `FetchContent` on first configure;
   no manual installation needed.*

2. **GLM** — math library (vectors, matrices) for the rendering pipeline.
   Version 1.0.3, header-only.
   *Source: fetched automatically by CMake `FetchContent` on first configure;
   no manual installation needed.*

3. **OpenGL** — the graphics API. Functions are loaded at runtime via
   `glfwGetProcAddress` (no GLAD/GLEW required).
   *Source: provided by the system (macOS frameworks, Linux Mesa, Windows
   drivers); discovered by `find_package(OpenGL REQUIRED)`.*

Additionally, the build toolchain itself is required: CMake (>= 3.16), a
C++17 compiler, a build tool (Make/Ninja), and network access on the first
configure so FetchContent can clone GLFW and GLM. Subsequent builds reuse
the cached `build/_deps` sources.

## System prerequisites (installation)

### macOS
```bash
xcode-select --install            # compiler tools (Clang, make) + OpenGL frameworks
brew install cmake                # CMake >= 3.16
```

### Ubuntu / Debian
```bash
sudo apt update
sudo apt install -y build-essential cmake git \
    libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev \
    libgl1-mesa-dev
```
(X11 packages are required to build GLFW on Linux; OpenGL is provided via Mesa.)


### Windows
- Install **Visual Studio** (Desktop development with C++) or MSVC Build Tools, **CMake** (>= 3.16), and **Git**.
- OpenGL drivers are provided by the system; GLFW/GLM remain managed automatically by FetchContent (no manual installation).

## Build (with dependency management)
From the project root (network access required on the first configure to download GLFW/GLM):
```bash
cmake -S . -B build
cmake --build build
```
- `cmake -S . -B build` configures the project and automatically resolves GLFW/GLM (FetchContent, pinned versions).
- `cmake --build build` compiles the executable.

The configured project version is reported by CMake and embedded in the generated header `build/generated/version.h` (from `${PROJECT_VERSION}`); the application prints and uses `Flower3D v1.1.2` at runtime.

## Tests
Tests are integrated with CTest (enabled by default via `BUILD_TESTING=ON`). From the project root after configuring/building:
```bash
ctest --test-dir build --output-on-failure
```
This runs the C++ unit tests (e.g. `flower_geometry`, which validates generated flower geometry without requiring a display/GPU).

## Packaging

Generate a distributable package with CPack:

```bash
cmake -S . -B build
cmake --build build
cpack --config build/CPackConfig.cmake
```

Packages are created in the project root (e.g. `Flower3D-1.1.2-Darwin.zip`
or `Flower3D-1.1.2-Darwin.pkg`). You can also validate the install rules
independently without generating a package:

```bash
cmake --install build --prefix install-test
```

### Running an installed copy

Extract the package and run the binary:

```bash
unzip Flower3D-1.1.2-Darwin.zip
Flower3D-1.1.2-Darwin/bin/flower3d
```

**Note:** The application loads shaders from a relative `shaders/` path
(see `src/renderer.cpp:29`). The package installs shaders to
`share/flower3d/shaders/`, so run the binary from a directory where the
`shaders/` folder is reachable, or copy the `shaders/` next to the binary.
System OpenGL drivers and GLFW runtime libraries remain external
prerequisites — see [System prerequisites](#system-prerequisites).

## Run
```bash
./build/flower3d
```
Run from the project root so the `shaders/` directory can be resolved.

## Controls
- Left drag: orbit camera
- Shift + left drag: orbit around current view target
- Scroll: zoom
- Esc: quit
