#include "camera.hpp"
#include <glm/ext/matrix_transform.hpp>

Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget) : cameraPosition(cameraPosition), cameraTarget(cameraTarget)
{
    cameraUp = calculateCameraUp();
}

glm::mat4 Camera::getView() const
{
    return glm::lookAt(cameraPosition, cameraTarget, cameraUp);
}

glm::vec3 Camera::getCameraPosition()
{
    return cameraPosition;
}

glm::vec3 Camera::calculateCameraUp()
{
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 cameraDirection = glm::normalize(cameraPosition - cameraTarget);
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
    return glm::cross(cameraDirection, cameraRight);
}

void FollowingCamera::updateCamera(glm::vec3 position)
{
    cameraTarget = position;
    cameraUp = calculateCameraUp();
}

void ThirdPersonCamera::updateCamera(glm::vec3 position, glm::vec3 front, glm::vec3 up)
{
    cameraPosition = position;
    cameraTarget = position + 10.0f * front;
    cameraUp = up;
}

glm::mat4 ThirdPersonCamera::getView() const
{
    return glm::lookAt(cameraPosition + 0.1f * cameraUp, cameraTarget + +0.1f * cameraUp, cameraUp);
}
