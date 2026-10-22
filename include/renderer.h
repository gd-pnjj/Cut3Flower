#pragma once

#include <memory>
#include <glm/glm.hpp>

class Shader;
class Camera;
class Flower;

class Renderer {
public:
    Renderer();
    ~Renderer();

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    Renderer& operator=(Renderer&&) = delete;

    void initialize();
    void render(const Camera& camera, float rotationAngle, float time);
    void resize(int width, int height);
    void cleanup();

private:
    struct Impl;
    std::unique_ptr<Impl> pImpl_;
};