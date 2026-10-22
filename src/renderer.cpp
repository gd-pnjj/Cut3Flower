#include "renderer.h"
#include "shader.h"
#include "camera.h"
#include "flower.h"
#include "gl_loader.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <iostream>

struct Renderer::Impl {
    Shader shader;
    Flower flower;
    GLuint vao_{0};
    GLuint vbo_{0};
    GLuint ebo_{0};
    bool initialized_{false};

    Impl() : flower(8, 16, 1.0f, 0.5f) {}

    ~Impl() {
        cleanup();
    }

    void initialize() {
        if (initialized_) return;

        shader = Shader("shaders/flower.vert", "shaders/flower.frag");

        gl::glGenVertexArrays(1, &vao_);
        gl::glGenBuffers(1, &vbo_);
        gl::glGenBuffers(1, &ebo_);

        gl::glBindVertexArray(vao_);

        gl::glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        gl::glBufferData(GL_ARRAY_BUFFER, 
            flower.getVertices().size() * sizeof(Vertex), 
            flower.getVertices().data(), 
            GL_STATIC_DRAW);

        gl::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
        gl::glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
            flower.getIndices().size() * sizeof(unsigned int), 
            flower.getIndices().data(), 
            GL_STATIC_DRAW);

        gl::glEnableVertexAttribArray(0);
        gl::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

        gl::glEnableVertexAttribArray(1);
        gl::glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

        gl::glEnableVertexAttribArray(2);
        gl::glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

        gl::glBindVertexArray(0);

        initialized_ = true;
    }

    void cleanup() {
        if (vao_) {
            gl::glDeleteVertexArrays(1, &vao_);
            vao_ = 0;
        }
        if (vbo_) {
            gl::glDeleteBuffers(1, &vbo_);
            vbo_ = 0;
        }
        if (ebo_) {
            gl::glDeleteBuffers(1, &ebo_);
            ebo_ = 0;
        }
        initialized_ = false;
    }

    void render(const Camera& camera, float rotationAngle, float time) {
        if (!initialized_) return;

        shader.use();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, 0.3f * sin(time * 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));

        shader.setUniform("model", glm::value_ptr(model), 1, false);
        shader.setUniform("view", glm::value_ptr(camera.getViewMatrix()), 1, false);
        shader.setUniform("projection", glm::value_ptr(camera.getProjectionMatrix()), 1, false);

        shader.setUniform("light.position", 2.0f, 3.0f, 4.0f);
        shader.setUniform("light.ambient", 0.2f, 0.2f, 0.2f);
        shader.setUniform("light.diffuse", 0.8f, 0.8f, 0.8f);
        shader.setUniform("light.specular", 1.0f, 1.0f, 1.0f);

        shader.setUniform("material.ambient", 0.8f, 0.3f, 0.3f);
        shader.setUniform("material.diffuse", 0.9f, 0.4f, 0.4f);
        shader.setUniform("material.specular", 0.5f, 0.5f, 0.5f);
        shader.setUniform("material.shininess", 32.0f);

        shader.setUniform("viewPos", camera.getPosition());

        gl::glBindVertexArray(vao_);
        gl::glDrawElements(GL_TRIANGLES, flower.getIndexCount(), GL_UNSIGNED_INT, 0);
        gl::glBindVertexArray(0);
    }
};

Renderer::Renderer() : pImpl_(std::make_unique<Impl>()) {}
Renderer::~Renderer() = default;

void Renderer::initialize() {
    pImpl_->initialize();
}

void Renderer::render(const Camera& camera, float rotationAngle, float time) {
    pImpl_->render(camera, rotationAngle, time);
}

void Renderer::resize(int width, int height) {
    gl::glViewport(0, 0, width, height);
}

void Renderer::cleanup() {
    pImpl_->cleanup();
}