#pragma once

#include <glm/vec3.hpp>

using namespace glm;

struct Light
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct DirLight : public Light
{
    vec3 direction;
};

struct PointLight : public Light
{
    vec3 position;

    float constant;
    float linear;
    float quadratic;
};

struct SpotLight : public Light
{
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;
};