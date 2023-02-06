#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include "movablemodel.hpp"
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

    glm::vec3 getPosition() const;
private:
    static constexpr float pitchAngle = 0.1f;
    static constexpr float yawAngle = 0.1f;
    static constexpr float rollAngle = 0.1f;
    static constexpr float acceleration = 0.2f;
    static constexpr float maxSpeed = 4;

    static constexpr float scale = 0.012f;

    float velocity = 0;

    std::shared_ptr<ThirdPersonCamera> thirdPersonCamera;
    std::shared_ptr<FollowingCamera> followingCamera;

    void calculateModelMatrix() override;
};