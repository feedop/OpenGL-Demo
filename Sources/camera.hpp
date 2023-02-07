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
	virtual ~Camera() = default;
	glm::vec3 calculateCameraUp();
public:
	virtual glm::mat4 getView(bool invertDirection = false) const;
	virtual glm::mat4 getProjection() const = 0;
	glm::vec3 getCameraPosition();
};

// Represents a camera that can be moved by keyboard input
class StaticCamera : public Camera
{
public:
	StaticCamera(glm::vec3 cameraPosition, glm::vec3 cameraTarget);
	glm::mat4 getProjection() const override;
};

class FollowingCamera : public Camera
{
public:
	FollowingCamera(glm::vec3 cameraPosition, glm::vec3 cameraTarget);
	void updateCamera(glm::vec3 position);
	glm::mat4 getProjection() const override;
};

class ThirdPersonCamera : public Camera
{
private:
	glm::vec3 cameraFront;
public:
	ThirdPersonCamera(glm::vec3 cameraPosition, glm::vec3 cameraTarget);
	void updateCamera(glm::vec3 position, glm::vec3 front, glm::vec3 up);
	glm::mat4 getView(bool invertDirection = false) const override;
	glm::mat4 getProjection() const override;
};