#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include <cmath>

Camera::Camera(float fov, float aspect, float near, float far)
    : fov_(fov), aspect_(aspect), near_(near), far_(far) {
    updateCameraVectors();
}

void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    xoffset *= mouseSensitivity_;
    yoffset *= mouseSensitivity_;

    yaw_ += xoffset;
    pitch_ += yoffset;

    if (constrainPitch) {
        pitch_ = std::clamp(pitch_, -89.0f, 89.0f);
    }

    updateCameraVectors();
    viewDirty_ = true;
}

void Camera::startOrbit() {
    target_ = position_ + front_ * distance_;
}

void Camera::endOrbit() {
    yaw_ = glm::degrees(std::atan2(front_.z, front_.x));
    pitch_ = glm::degrees(std::asin(std::clamp(front_.y, -1.0f, 1.0f)));
    viewDirty_ = true;
}

void Camera::processOrbit(float xoffset, float yoffset) {
    xoffset *= mouseSensitivity_;
    yoffset *= mouseSensitivity_;

    yaw_ += xoffset;
    pitch_ += yoffset;
    pitch_ = std::clamp(pitch_, -89.0f, 89.0f);

    glm::vec3 viewDir;
    viewDir.x = std::cos(glm::radians(pitch_)) * std::cos(glm::radians(yaw_));
    viewDir.y = std::sin(glm::radians(pitch_));
    viewDir.z = std::cos(glm::radians(pitch_)) * std::sin(glm::radians(yaw_));
    viewDir = glm::normalize(viewDir);

    position_ = target_ - distance_ * viewDir;
    front_ = viewDir;
    right_ = glm::normalize(glm::cross(front_, worldUp_));
    up_ = glm::normalize(glm::cross(right_, front_));
    viewDirty_ = true;
}

void Camera::processMouseScroll(float yoffset) {
    fov_ -= yoffset * scrollSensitivity_;
    fov_ = std::clamp(fov_, 1.0f, 90.0f);
    projectionDirty_ = true;
}

void Camera::update(float deltaTime) {
    (void)deltaTime;
    // No keyboard movement for this simple camera
}

const glm::mat4& Camera::getViewMatrix() const {
    if (viewDirty_) {
        viewMatrix_ = glm::lookAt(position_, position_ + front_, up_);
        viewDirty_ = false;
    }
    return viewMatrix_;
}

const glm::mat4& Camera::getProjectionMatrix() const {
    if (projectionDirty_) {
        projectionMatrix_ = glm::perspective(glm::radians(fov_), aspect_, near_, far_);
        projectionDirty_ = false;
    }
    return projectionMatrix_;
}

const glm::vec3& Camera::getPosition() const {
    return position_;
}

void Camera::setAspectRatio(float aspect) {
    aspect_ = aspect;
    projectionDirty_ = true;
}

void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front.y = sin(glm::radians(pitch_));
    front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front_ = glm::normalize(front);
    right_ = glm::normalize(glm::cross(front_, worldUp_));
    up_ = glm::normalize(glm::cross(right_, front_));
}