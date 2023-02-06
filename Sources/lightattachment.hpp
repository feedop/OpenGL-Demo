#pragma once

#include <glm/vec3.hpp>

#include "light.hpp"

class LightAttachment
{
protected:
	float relativeFront;
	float relativeRight;
	float relativeUp;

	LightAttachment(float relativeFront, float relativeRight, float relativeUp);
};

class PointLightAttachment : public LightAttachment
{
private:
	PointLight* pointLight;
public:
	PointLightAttachment(float relativeFront, float relativeRight, float relativeUp, PointLight* pointLight);
	void updatePosition(glm::vec3 position, glm::vec3 front, glm::vec3 right, glm::vec3 up);
};

class SpotLightAttachment : public LightAttachment
{
private:
	SpotLight* spotLight;
	bool invertDirection;
public:
	SpotLightAttachment(float relativeFront, float relativeRight, float relativeUp, SpotLight* spotLight, bool invertDirection);
	void updatePosition(glm::vec3 position, glm::vec3 front, glm::vec3 right, glm::vec3 up, glm::vec3 direction);
	bool getInvertDirection();
};