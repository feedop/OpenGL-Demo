#include "lightattachment.hpp"

LightAttachment::LightAttachment(float relativeFront, float relativeRight, float relativeUp) :
	relativeFront(relativeFront), relativeRight(relativeRight), relativeUp(relativeUp) {}

PointLightAttachment::PointLightAttachment(float relativeFront, float relativeRight, float relativeUp, PointLight* pointLight) :
	LightAttachment(relativeFront, relativeRight, relativeUp), pointLight(pointLight)
{}

void PointLightAttachment::updatePosition(glm::vec3 position, glm::vec3 front, glm::vec3 right, glm::vec3 up)
{
	pointLight->position = position + relativeFront * front + relativeRight * right + relativeUp * up;
}

SpotLightAttachment::SpotLightAttachment(float relativeFront, float relativeRight, float relativeUp, SpotLight* spotLight) :
	LightAttachment(relativeFront, relativeRight, relativeUp), spotLight(spotLight) {}

void SpotLightAttachment::updatePosition(glm::vec3 position, glm::vec3 front, glm::vec3 right, glm::vec3 up, glm::vec3 direction)
{
	spotLight->position = position + relativeFront * front + relativeRight * right + relativeUp * up;
	spotLight->direction = direction;
}
