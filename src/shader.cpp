#include "shader.h"
#include "gl_loader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vertexCode = readFile(vertexPath);
    std::string fragmentCode = readFile(fragmentPath);

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    GLuint vertex = gl::glCreateShader(GL_VERTEX_SHADER);
    gl::glShaderSource(vertex, 1, &vShaderCode, nullptr);
    gl::glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    GLuint fragment = gl::glCreateShader(GL_FRAGMENT_SHADER);
    gl::glShaderSource(fragment, 1, &fShaderCode, nullptr);
    gl::glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    program_ = gl::glCreateProgram();
    gl::glAttachShader(program_, vertex);
    gl::glAttachShader(program_, fragment);
    gl::glLinkProgram(program_);
    checkCompileErrors(program_, "PROGRAM");

    gl::glDeleteShader(vertex);
    gl::glDeleteShader(fragment);
}

Shader::~Shader() {
    if (program_ != 0) {
        gl::glDeleteProgram(program_);
        program_ = 0;
    }
}

Shader::Shader(Shader&& other) noexcept : program_(other.program_) {
    other.program_ = 0;
}

Shader& Shader::operator=(Shader&& other) noexcept {
    if (this != &other) {
        if (program_ != 0) {
            gl::glDeleteProgram(program_);
        }
        program_ = other.program_;
        other.program_ = 0;
    }
    return *this;
}

void Shader::use() const {
    gl::glUseProgram(program_);
}

GLuint Shader::getProgram() const {
    return program_;
}

void Shader::setUniform(const std::string& name, bool value) const {
    gl::glUniform1i(gl::glGetUniformLocation(program_, name.c_str()), static_cast<int>(value));
}

void Shader::setUniform(const std::string& name, int value) const {
    gl::glUniform1i(gl::glGetUniformLocation(program_, name.c_str()), value);
}

void Shader::setUniform(const std::string& name, float value) const {
    gl::glUniform1f(gl::glGetUniformLocation(program_, name.c_str()), value);
}

void Shader::setUniform(const std::string& name, float x, float y, float z) const {
    gl::glUniform3f(gl::glGetUniformLocation(program_, name.c_str()), x, y, z);
}

void Shader::setUniform(const std::string& name, const glm::vec3& value) const {
    gl::glUniform3fv(gl::glGetUniformLocation(program_, name.c_str()), 1, &value[0]);
}

void Shader::setUniform(const std::string& name, const float* value, int count) const {
    gl::glUniform1fv(gl::glGetUniformLocation(program_, name.c_str()), count, value);
}

void Shader::setUniform(const std::string& name, const float* matrix, int count, bool transpose) const {
    gl::glUniformMatrix4fv(gl::glGetUniformLocation(program_, name.c_str()), count, transpose, matrix);
}

void Shader::checkCompileErrors(GLuint shader, const std::string& type) const {
    GLint success;
    char infoLog[1024];
    if (type != "PROGRAM") {
        gl::glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            gl::glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n";
        }
    } else {
        gl::glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            gl::glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n";
        }
    }
}

std::string Shader::readFile(const std::string& path) const {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "ERROR::SHADER::FILE_NOT_FOUND: " << path << "\n";
        return "";
    }
    std::stringstream stream;
    stream << file.rdbuf();
    return stream.str();
}