#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include "model.hpp"
#include "camera.hpp"

class PlayerModel : public MovableModel
{
public:
    PlayerModel(const char* path);
    void attachThirdPersonCamera(std::shared_ptr<ThirdPersonCamera> thirdPersonCamera);
    void attachFollowingCamera(std::shared_ptr<FollowingCamera> followingCamera);

    void move() override;

    void diveDown();
    void pullUp();
    void turnLeft();
    void turnRight();

    void increaseVelocity();
    void decreaseVelocity();
    void rollLeft();
    void rollRight();
private:
    static constexpr float pitchAngle = 0.1f;
    static constexpr float yawAngle = 0.1f;
    static constexpr float rollAngle = 0.1f;
    static constexpr float acceleration = 0.01f;
    static constexpr float maxSpeed = 0.1f;

    static constexpr float scale = 0.001f;

    float velocity = 0;
    glm::mat4 rotationMatrix = glm::mat4(1.0f);

    glm::vec3 front = glm::vec3(0, 0, 1);
    glm::vec3 right = glm::vec3(-1, 0, 0);
    glm::vec3 up = glm::vec3(0, 1, 0);

    std::shared_ptr<ThirdPersonCamera> thirdPersonCamera;
    std::shared_ptr<FollowingCamera> followingCamera;

    void calculateModelMatrix();
};