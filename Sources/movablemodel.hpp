#pragma once

#include <vector>
#include <memory>

#include "model.hpp"

class MovableModel : public Model
{
public:
    virtual void move() = 0;
    void setPosition(glm::vec3 position);
    void attachPointLight(float relativeFront, float relativeRight, float relativeUp, PointLight* pointLight);
    void attachSpotLight(float relativeFront, float relativeRight, float relativeUp, SpotLight* spotLight, bool invertDirection = false);
    void updateAttachedLights();

protected:
    MovableModel(const char* path);

    glm::mat4 rotationMatrix = glm::mat4(1.0f);

    glm::vec3 front = glm::vec3(0, 0, 1);
    glm::vec3 right = glm::vec3(-1, 0, 0);
    glm::vec3 up = glm::vec3(0, 1, 0);

    glm::vec3 position = glm::vec3(0, 0, 0);
    std::vector<std::shared_ptr<PointLightAttachment>> attachedPointLights;
    std::vector<std::shared_ptr<SpotLightAttachment>> attachedSpotLights;

    virtual void calculateModelMatrix() = 0;
};