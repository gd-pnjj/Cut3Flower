#pragma once

#include <string>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Shader {
public:
    Shader() = default;
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;
    Shader(Shader&& other) noexcept;
    Shader& operator=(Shader&& other) noexcept;

    void use() const;
    GLuint getProgram() const;

    void setUniform(const std::string& name, bool value) const;
    void setUniform(const std::string& name, int value) const;
    void setUniform(const std::string& name, float value) const;
    void setUniform(const std::string& name, float x, float y, float z) const;
    void setUniform(const std::string& name, const glm::vec3& value) const;
    void setUniform(const std::string& name, const float* value, int count) const;
    void setUniform(const std::string& name, const float* matrix, int count, bool transpose) const;

private:
    GLuint program_{0};
    void checkCompileErrors(GLuint shader, const std::string& type) const;
    std::string readFile(const std::string& path) const;
};