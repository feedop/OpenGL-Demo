#pragma once

#include <glm/vec3.hpp>

using namespace glm;

struct Light
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    /*Light(vec3 ambient, vec3 diffuse, vec3 specular) : ambient(ambient), diffuse(diffuse), specular(specular) {}*/
};

struct DirLight : public Light
{
    vec3 direction;

    /*DirLight(vec3 ambient, vec3 diffuse, vec3 specular, vec3 direction) : Light(ambient, diffuse, specular),
        direction(direction) {}*/
};

struct PointLight : public Light
{
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    /*PointLight(vec3 ambient, vec3 diffuse, vec3 specular, vec3 direction) : Light(ambient, diffuse, specular),
        position(position) {}*/
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