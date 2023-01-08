#pragma once
#include <vector>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include "shader.hpp"
#include "model.hpp"

class ViewModel
{
public:
    int selectedShader = 0;
    int selectedCamera = 0;


    ViewModel();
    void Draw();
private:
    // model data
    std::vector<Model> models;
    std::vector<Shader>shaders;

    glm::mat4 m_view = glm::mat4(1.0f);
    glm::mat4 m_projection = glm::mat4(1.0f);

    glm::vec3 m_lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

};