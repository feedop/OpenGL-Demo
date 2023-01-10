#pragma once
#include <vector>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include "shader.hpp"
#include "model.hpp"
#include "light.hpp"

#define NR_DIR_LIGHTS 1
#define NR_POINT_LIGHTS 1
#define NR_SPOT_LIGHTS 2

using namespace glm;

class ViewModel
{
public:
    int selectedShader = 2;
    int selectedCamera = 0;

    ViewModel();
    ~ViewModel();
    void Draw();
private:
    // model data
    std::vector<Model> models;
    std::vector<Shader*>shaders;

    std::vector<DirLight> dirLights;
    std::vector<PointLight> pointLights;
    std::vector<SpotLight> spotLights;

    mat4 m_view = mat4(1.0f);
    mat4 m_projection = mat4(1.0f);

};