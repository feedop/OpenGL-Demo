#include "movablemodel.hpp"

// Movable model abstract class

void MovableModel::setPosition(glm::vec3 position)
{
    this->position = position;
}

void MovableModel::attachPointLight(float relativeFront, float relativeRight, float relativeUp, PointLight* pointLight)
{
    attachedPointLights.emplace_back(std::make_shared<PointLightAttachment>(relativeFront, relativeRight, relativeUp, pointLight));
}

void MovableModel::attachSpotLight(float relativeFront, float relativeRight, float relativeUp, SpotLight* spotLight, bool invertDirection)
{
    attachedSpotLights.emplace_back(std::make_shared<SpotLightAttachment>(relativeFront, relativeRight, relativeUp, spotLight, invertDirection));
}

void MovableModel::updateAttachedLights()
{
    for (auto& pointLight : attachedPointLights)
    {
        pointLight->updatePosition(position, front, right, up);
    }

    for (auto& pointLight : attachedSpotLights)
    {
        if (pointLight->getInvertDirection())
            pointLight->updatePosition(position, front, right, up, -front);
        else
            pointLight->updatePosition(position, front, right, up, front);
    }
}

MovableModel::MovableModel(const char* path) : Model(path) {}