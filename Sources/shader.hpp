#pragma once

#include <string>
#include <vector>
#include <glm/gtc/type_ptr.hpp>

#include "light.hpp"
#include "material.hpp"

// https://learnopengl.com/Getting-started/Shaders
class Shader
{
public:
    // the program ID
    unsigned int ID;
    // use/activate the shader
    virtual ~Shader() {}
    virtual void use();
    // utility uniform functions
    virtual void setFloat(const char* name, float value) const;
    virtual void setVector(const char* name, glm::vec3 vector) const;
    virtual void setMatrix(const char* name, glm::mat4 matrix) const;
    virtual void setLighting(std::vector<DirLight>& dirLights, std::vector<PointLight>& pointLights, std::vector<SpotLight>& spotLights) const = 0;
    virtual void setMaterial(const Material& material) const = 0;
protected:
    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
};

class SolidColorShader : public Shader
{
public:
    SolidColorShader() : Shader("Shaders\\solidcolor.vert", "Shaders\\solidcolor.frag") {}
    void setLighting(std::vector<DirLight>& dirLights, std::vector<PointLight>& pointLights, std::vector<SpotLight>& spotLights) const override;
    void setMaterial(const Material& material) const override;
};

class GouraudShader : public Shader
{
public:
    GouraudShader() : Shader("Shaders\\gouraud.vert", "Shaders\\gouraud.frag") {}
    void setLighting(std::vector<DirLight>& dirLights, std::vector<PointLight>& pointLights, std::vector<SpotLight>& spotLights) const override;
    void setMaterial(const Material& material) const override;
};

class PhongShader : public Shader
{
public:
    PhongShader() : Shader("Shaders\\phong.vert", "Shaders\\phong.frag") {}
    void setLighting(std::vector<DirLight>& dirLights, std::vector<PointLight>& pointLights, std::vector<SpotLight>& spotLights) const override;
    void setMaterial(const Material& material) const override;
};