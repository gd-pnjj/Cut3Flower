#pragma once

#include <glm/glm.hpp>

class Camera {
public:
    Camera(float fov = 45.0f, float aspect = 1.0f, float near = 0.1f, float far = 100.0f);

    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void processOrbit(float xoffset, float yoffset);
    void startOrbit();
    void endOrbit();
    void processMouseScroll(float yoffset);
    void update(float deltaTime);

    const glm::mat4& getViewMatrix() const;
    const glm::mat4& getProjectionMatrix() const;
    const glm::vec3& getPosition() const;

    void setAspectRatio(float aspect);

private:
    void updateCameraVectors();

    glm::vec3 position_{0.0f, 1.0f, 5.0f};
    glm::vec3 front_{0.0f, 0.0f, -1.0f};
    glm::vec3 up_{0.0f, 1.0f, 0.0f};
    glm::vec3 right_{1.0f, 0.0f, 0.0f};
    glm::vec3 worldUp_{0.0f, 1.0f, 0.0f};
    glm::vec3 target_{0.0f, 0.0f, 0.0f};
    float distance_{5.0f};

    float yaw_{-90.0f};
    float pitch_{0.0f};
    float fov_{45.0f};
    float aspect_{1.0f};
    float near_{0.1f};
    float far_{100.0f};

    float mouseSensitivity_{0.1f};
    float scrollSensitivity_{1.0f};

    mutable glm::mat4 viewMatrix_{1.0f};
    mutable glm::mat4 projectionMatrix_{1.0f};
    mutable bool viewDirty_{true};
    mutable bool projectionDirty_{true};
};