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
    int selectedCamera = 0;

    Presenter(Repository* repository);
    void draw();
    void updateCamera(vec3 position, vec3 front);
    void rotateCameraSideways(float angle);
private:
    Repository* repository;

    std::vector<std::shared_ptr<Shader>> shaders;
    std::vector<std::shared_ptr<Camera>> cameras;

    std::shared_ptr<Shader> skyboxShader;
    Skybox skybox{};

    mat4 m_view = mat4(1.0f); /*glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f));*/
    mat4 m_projection = mat4(1.0f);
};