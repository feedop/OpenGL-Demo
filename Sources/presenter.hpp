#pragma once
#include <vector>
#include <memory>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include "repository.hpp"
#include "shader.hpp"
#include "model.hpp"
#include "light.hpp"
#include "camera.hpp"
#include "textures/skybox.hpp"

using namespace glm;

class Presenter
{
public:
    int selectedShader = 2;
    int selectedCamera = 2;
    bool invertThirdPersonCamera = false;
    bool night = false;
    int nightFrames = 0;
    constexpr static int maxFrames = 180;
    constexpr static float frameCoefficient = 1.0f / static_cast<float>(maxFrames);
    float fogDensity = 0.0f;
    glm::vec3 fogColor { 1.0f, 1.0f, 1.0f };

    Presenter(Repository* repository);
    void draw();
    void countFramesForNight();
private:
    Repository* repository;
    unsigned int gBuffer = 0;

    std::shared_ptr<StaticCamera> staticCamera;
    std::shared_ptr<FollowingCamera> followingCamera;
    std::shared_ptr<ThirdPersonCamera> thirdPersonCamera;

    std::vector<std::shared_ptr<Shader>> shaders;
    std::vector<std::shared_ptr<Camera>> cameras;

    std::shared_ptr<Shader> skyboxShader;
    Skybox skybox{};

    glm::vec3 dirLightAmbient;
    glm::vec3 dirLightDiffuse;
    glm::vec3 dirLightSpecular;
};