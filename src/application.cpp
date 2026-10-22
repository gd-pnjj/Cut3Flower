#include "application.h"
#include "renderer.h"
#include "camera.h"
#include "gl_loader.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>

struct Application::Impl {
    GLFWwindow* window_{nullptr};
    int width_{800};
    int height_{600};
    const char* title_{"3D Flower"};
    
    std::unique_ptr<Renderer> renderer_;
    std::unique_ptr<Camera> camera_;
    
    float lastX_{400.0f};
    float lastY_{300.0f};
    bool firstMouse_{true};
    bool leftMousePressed_{false};
    bool shiftPressed_{false};
    
    float rotationAngle_{0.0f};
    float rotationSpeed_{0.5f};
    
    std::chrono::steady_clock::time_point lastTime_;
    float deltaTime_{0.0f};
};

Application::Application(int width, int height, const char* title) 
    : pImpl_(std::make_unique<Impl>()) {
    pImpl_->width_ = width;
    pImpl_->height_ = height;
    pImpl_->title_ = title;
    pImpl_->renderer_ = std::make_unique<Renderer>();
    pImpl_->camera_ = std::make_unique<Camera>(45.0f, static_cast<float>(width) / height, 0.1f, 100.0f);
    pImpl_->lastTime_ = std::chrono::steady_clock::now();
}

Application::~Application() {
    shutdown();
}

bool Application::initialize() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    pImpl_->window_ = glfwCreateWindow(pImpl_->width_, pImpl_->height_, pImpl_->title_, nullptr, nullptr);
    if (pImpl_->window_) {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        if (mode) {
            int x = (mode->width - pImpl_->width_) / 2;
            int y = (mode->height - pImpl_->height_) / 2;
            glfwSetWindowPos(pImpl_->window_, x, y);
        }
    }
    if (!pImpl_->window_) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(pImpl_->window_);
    glfwSetFramebufferSizeCallback(pImpl_->window_, framebufferSizeCallback);
    glfwSetCursorPosCallback(pImpl_->window_, mouseCallback);
    glfwSetScrollCallback(pImpl_->window_, scrollCallback);
    glfwSetWindowUserPointer(pImpl_->window_, this);

    // Initialize GL loader
    gl::load();

    gl::glEnable(GL_DEPTH_TEST);
    gl::glEnable(GL_CULL_FACE);
    gl::glCullFace(GL_BACK);
    gl::glFrontFace(GL_CCW);

    pImpl_->renderer_->initialize();

    return true;
}

void Application::run() {
    while (!glfwWindowShouldClose(pImpl_->window_)) {
        auto currentTime = std::chrono::steady_clock::now();
        pImpl_->deltaTime_ = std::chrono::duration<float>(currentTime - pImpl_->lastTime_).count();
        pImpl_->lastTime_ = currentTime;

        processInput(pImpl_->deltaTime_);
        update(pImpl_->deltaTime_);
        render();

        glfwSwapBuffers(pImpl_->window_);
        glfwPollEvents();
    }
}

void Application::shutdown() {
    if (pImpl_->renderer_) {
        pImpl_->renderer_->cleanup();
    }
    if (pImpl_->window_) {
        glfwDestroyWindow(pImpl_->window_);
        pImpl_->window_ = nullptr;
    }
    glfwTerminate();
}

void Application::processInput(float deltaTime) {
    (void)deltaTime;
    if (glfwGetKey(pImpl_->window_, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(pImpl_->window_, true);
    }


    if (glfwGetMouseButton(pImpl_->window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        if (!pImpl_->leftMousePressed_) {
            pImpl_->leftMousePressed_ = true;
            double xpos, ypos;
            glfwGetCursorPos(pImpl_->window_, &xpos, &ypos);
            pImpl_->lastX_ = static_cast<float>(xpos);
            pImpl_->lastY_ = static_cast<float>(ypos);
            pImpl_->firstMouse_ = true;
        }
    } else {
        pImpl_->leftMousePressed_ = false;
    }
}

void Application::update(float deltaTime) {
    pImpl_->rotationAngle_ += pImpl_->rotationSpeed_ * deltaTime;
    if (pImpl_->rotationAngle_ > 2.0f * 3.14159265f) {
        pImpl_->rotationAngle_ -= 2.0f * 3.14159265f;
    }
    pImpl_->camera_->update(deltaTime);
}

void Application::render() {
    gl::glClearColor(244.0f/255.0f, 248.0f/255.0f, 244.0f/255.0f, 1.0f);
    gl::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float time = std::chrono::duration<float>(std::chrono::steady_clock::now() - pImpl_->lastTime_).count();
    pImpl_->renderer_->render(*pImpl_->camera_, pImpl_->rotationAngle_, time);
}

void Application::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (app) {
        app->pImpl_->width_ = width;
        app->pImpl_->height_ = height;
        app->pImpl_->renderer_->resize(width, height);
        app->pImpl_->camera_->setAspectRatio(static_cast<float>(width) / height);
    }
}

void Application::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (!app || !app->pImpl_->leftMousePressed_) return;

    if (app->pImpl_->firstMouse_) {
        app->pImpl_->lastX_ = static_cast<float>(xpos);
        app->pImpl_->lastY_ = static_cast<float>(ypos);
        app->pImpl_->firstMouse_ = false;
    }

    float xoffset = static_cast<float>(xpos) - app->pImpl_->lastX_;
    float yoffset = app->pImpl_->lastY_ - static_cast<float>(ypos);
    app->pImpl_->lastX_ = static_cast<float>(xpos);
    app->pImpl_->lastY_ = static_cast<float>(ypos);

    bool shiftNow = glfwGetKey(app->pImpl_->window_, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
                    glfwGetKey(app->pImpl_->window_, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS;
    if (shiftNow && !app->pImpl_->shiftPressed_) {
        app->pImpl_->camera_->startOrbit();
    }
    if (!shiftNow && app->pImpl_->shiftPressed_) {
        app->pImpl_->camera_->endOrbit();
        app->pImpl_->firstMouse_ = true;
    }
    app->pImpl_->shiftPressed_ = shiftNow;
    if (shiftNow) {
        app->pImpl_->camera_->processOrbit(xoffset, yoffset);
    } else {
        app->pImpl_->camera_->processMouseMovement(xoffset, yoffset);
    }
}

void Application::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    (void)xoffset;
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (app) {
        app->pImpl_->camera_->processMouseScroll(static_cast<float>(yoffset));
    }
}