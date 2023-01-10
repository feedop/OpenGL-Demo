#pragma once

#include <glm/vec3.hpp>

using namespace glm;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;

    static Material whitePlastic()
    {
        return
        {
            vec3(0, 0, 0),
            vec3(0.55f, 0.55f, 0.55f),
            vec3(0.7f, 0.7f, 0.7f),
            32
        };
    }
};