#include "playermodel.hpp"

PlayerModel::PlayerModel(const char* path) : MovableModel(path)
{}

void PlayerModel::attachThirdPersonCamera(std::shared_ptr<ThirdPersonCamera> thirdPersonCamera)
{
	this->thirdPersonCamera = thirdPersonCamera;
	thirdPersonCamera->updateCamera(position, front, up);
}

void PlayerModel::attachFollowingCamera(std::shared_ptr<FollowingCamera> followingCamera)
{
	this->followingCamera = followingCamera;
	followingCamera->updateCamera(position);
}

void PlayerModel::move()
{
	if (velocity == 0)
		return;

	position += front * velocity;
	calculateModelMatrix();
	followingCamera->updateCamera(position);
	thirdPersonCamera->updateCamera(position, front, up);
}

void PlayerModel::diveDown()
{
	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), -pitchAngle, right);
	rotationMatrix = rotation * rotationMatrix;
	front = rotation * glm::vec4(front, 1.0f);
	up = rotation * glm::vec4(up, 1.0f);

	calculateModelMatrix();
	thirdPersonCamera->updateCamera(position, front, up);
}

void PlayerModel::pullUp()
{
	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), pitchAngle, right);
	rotationMatrix = rotation * rotationMatrix;
	front = rotation * glm::vec4(front, 1.0f);
	up = rotation * glm::vec4(up, 1.0f);

	calculateModelMatrix();
	thirdPersonCamera->updateCamera(position, front, up);
}

void PlayerModel::turnLeft()
{
	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), yawAngle, up);
	rotationMatrix = rotation * rotationMatrix;
	front =  rotation * glm::vec4(front, 1.0f);
	right = rotation * glm::vec4(right, 1.0f);

	calculateModelMatrix();
	thirdPersonCamera->updateCamera(position, front, up);
}

void PlayerModel::turnRight()
{
	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), -yawAngle, up);
	rotationMatrix = rotation * rotationMatrix;
	front = rotation * glm::vec4(front, 1.0f);
	right = rotation * glm::vec4(right, 1.0f);

	calculateModelMatrix();
	thirdPersonCamera->updateCamera(position, front, up);
}

void PlayerModel::increaseVelocity()
{
	if (velocity < maxSpeed)
		velocity += acceleration;
}

void PlayerModel::decreaseVelocity()
{
	if (velocity > 0)
		velocity -= acceleration;
}

void PlayerModel::rollLeft()
{
	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), -rollAngle, front);
	rotationMatrix = rotation * rotationMatrix;
	up = rotation * glm::vec4(up, 1.0f);
	right = rotation * glm::vec4(right, 1.0f);

	calculateModelMatrix();
	thirdPersonCamera->updateCamera(position, front, up);
}

void PlayerModel::rollRight()
{
	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), rollAngle, front);
	rotationMatrix = rotation * rotationMatrix;
	up = rotation * glm::vec4(up, 1.0f);
	right = rotation * glm::vec4(right, 1.0f);

	calculateModelMatrix();
	thirdPersonCamera->updateCamera(position, front, up);
}

void PlayerModel::calculateModelMatrix()
{
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale));
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
	modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}