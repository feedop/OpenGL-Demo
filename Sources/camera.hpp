#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Camera
{
protected:
	glm::vec3 cameraPosition;
	glm::vec3 cameraTarget;
	glm::vec3 cameraUp;
public:
	Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget);
	glm::mat4 getLookAt();
	glm::vec3 getCameraPosition();
	glm::vec3 getTargetPosition();
	glm::vec3 calculateCameraUp();
	float getDistanceToTarget();
	virtual void updateCamera(glm::vec3 position, glm::vec3 front) = 0;
};

// Represents a camera that can be moved by keyboard input
class MovableCamera : public Camera
{
public:
	MovableCamera(glm::vec3 cameraPosition, glm::vec3 cameraTarget) : Camera(cameraPosition, cameraTarget) {}
	void updateCamera(glm::vec3 position, glm::vec3 front) override;
};

class FollowingCamera : public Camera
{
public:
	FollowingCamera(glm::vec3 cameraPosition, glm::vec3 cameraTarget) : Camera(cameraPosition, cameraTarget) {}
	void updateCamera(glm::vec3 position, glm::vec3 front) override;
};

class ThirdPersonCamera : public Camera
{
public:
	ThirdPersonCamera(glm::vec3 cameraPosition, glm::vec3 cameraTarget) : Camera(cameraPosition, cameraTarget) {}
	void updateCamera(glm::vec3 position, glm::vec3 front) override;
};