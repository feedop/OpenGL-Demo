#include "camera.hpp"
#include <glm/ext/matrix_transform.hpp>

Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget) : cameraPosition(cameraPosition), cameraTarget(cameraTarget)
{
    cameraUp = calculateCameraUp();
}

glm::mat4 Camera::getLookAt()
{
    return glm::lookAt(cameraPosition, cameraTarget, cameraUp);
}

glm::vec3 Camera::getCameraPosition()
{
    return cameraPosition;
}

glm::vec3 Camera::getTargetPosition()
{
    return cameraTarget;
}

glm::vec3 Camera::calculateCameraUp()
{
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 cameraDirection = glm::normalize(cameraPosition - cameraTarget);
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
    return glm::cross(cameraDirection, cameraRight);
}

float Camera::getDistanceToTarget()
{
    return glm::length(cameraTarget - cameraPosition);
}

void MovableCamera::updateCamera(glm::vec3 position, glm::vec3 front)
{
    cameraPosition = position;
}

void FollowingCamera::updateCamera(glm::vec3 position, glm::vec3 front)
{
    cameraTarget = position;
}

void ThirdPersonCamera::updateCamera(glm::vec3 position, glm::vec3 front)
{
    cameraPosition = position + glm::normalize(cameraUp);
}
