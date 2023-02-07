#pragma once

#include "movablemodel.hpp"

class AIModel : public MovableModel
{
public:
    AIModel(const char* path);
    void move(float verticalRotation = 0, float horizontalRotation = 0) override;
    void setParameters(float angularVelocity, glm::vec3 translation, glm::vec3 rotationAxis);
    void setRotationMatrix(glm::mat4 rotationMatrix);
    void rotateInitialCoordinateSystem(float angle);
    void rotate(float angle);
private:
    float angularVelocity = 0;
    glm::vec3 translation {};
    glm::vec3 rotationAxis { 0, 0,-1 };

    void calculateModelMatrix() override;
};