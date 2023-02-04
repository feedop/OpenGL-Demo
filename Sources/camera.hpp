#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Camera
{
protected:
	glm::vec3 cameraPosition;
	glm::vec3 cameraTarget;
	glm::vec3 cameraUp;

	Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget);
	glm::vec3 calculateCameraUp();
public:
	virtual glm::mat4 getView() const;
	glm::vec3 getCameraPosition();
};

// Represents a camera that can be moved by keyboard input
class StaticCamera : public Camera
{
public:
	StaticCamera(glm::vec3 cameraPosition, glm::vec3 cameraTarget) : Camera(cameraPosition, cameraTarget) {}
};

class FollowingCamera : public Camera
{
public:
	FollowingCamera(glm::vec3 cameraPosition, glm::vec3 cameraTarget) : Camera(cameraPosition, cameraTarget) {}
	void updateCamera(glm::vec3 position);
};

class ThirdPersonCamera : public Camera
{
public:
	ThirdPersonCamera(glm::vec3 cameraPosition, glm::vec3 cameraTarget) : Camera(cameraPosition, cameraTarget) {}
	void updateCamera(glm::vec3 position, glm::vec3 front, glm::vec3 up);
	glm::mat4 getView() const override;
};