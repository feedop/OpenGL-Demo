#include "aimodel.hpp"

AIModel::AIModel(const char* path) : MovableModel(path)
{}

void AIModel::move(float verticalRotation, float horizontalRotation)
{
	rotate(angularVelocity);
	updateAttachedLights();
}

void AIModel::setParameters(float angularVelocity, glm::vec3 translation, glm::vec3 rotationAxis)
{
	this->angularVelocity = angularVelocity;
	this->translation = translation;
	this->rotationAxis = rotationAxis;
}

void AIModel::setRotationMatrix(glm::mat4 rotationMatrix)
{
	this->rotationMatrix = rotationMatrix;
}

void AIModel::rotateInitialCoordinateSystem(float angle)
{
	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, right);
	front = rotation * glm::vec4(front, 1.0f);
	up = rotation * glm::vec4(up, 1.0f);
}

void AIModel::rotate(float angle)
{
	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, -up);
	rotationMatrix = rotation * rotationMatrix;
	front = rotation * glm::vec4(front, 1.0f);
	right = rotation * glm::vec4(right, 1.0f);

	calculateModelMatrix();
	position = modelMatrix[3];
}

void AIModel::calculateModelMatrix()
{
	modelMatrix = glm::translate(glm::mat4(1.0f), translation) * rotationMatrix;
}
