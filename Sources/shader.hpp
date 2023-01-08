#pragma once

#include <string>
#include <glm/gtc/type_ptr.hpp>

// https://learnopengl.com/Getting-started/Shaders
class Shader
{
public:
    // the program ID
    unsigned int ID;

    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    // use/activate the shader
    void use();
    // utility uniform functions
    void setVector(const char* name, glm::vec3 color) const;

    void setMatrix(const char* name, glm::mat4 matrix);
};