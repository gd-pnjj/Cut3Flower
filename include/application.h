#pragma once

#include <memory>
#include <GLFW/glfw3.h>

class Camera;
class Renderer;

class Application {
public:
    Application(int width = 800, int height = 600, const char* title = "3D Flower");
    ~Application();

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    bool initialize();
    void run();
    void shutdown();

private:
    void processInput(float deltaTime);
    void update(float deltaTime);
    void render();
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

    struct Impl;
    std::unique_ptr<Impl> pImpl_;
};