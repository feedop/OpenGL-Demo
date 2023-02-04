#pragma once

#include <string>
#include <vector>
#include <glm/gtc/type_ptr.hpp>

#include "light.hpp"

// https://learnopengl.com/Getting-started/Shaders
class Shader
{
public:
    // the program ID
    unsigned int ID;
    // use/activate the shader
    virtual ~Shader() = default;
    virtual void use();
    // utility uniform functions
    virtual void setFloat(const char* name, float value) const;
    virtual void setInt(const char* name, int value) const;
    virtual void setVector(const char* name, glm::vec3 vector) const;
    virtual void setMatrix(const char* name, glm::mat4 matrix) const;
    virtual void setLighting(const std::vector<DirLight>& dirLights, const std::vector<PointLight>& pointLights, const std::vector<SpotLight>& spotLights) const = 0;
protected:
    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
};

class SolidColorShader : public Shader
{
public:
    SolidColorShader();
    void setLighting(const std::vector<DirLight>& dirLights, const std::vector<PointLight>& pointLights, const std::vector<SpotLight>& spotLights) const override;
};

class GouraudShader : public Shader
{
public:
    GouraudShader();
    void setLighting(const std::vector<DirLight>& dirLights, const std::vector<PointLight>& pointLights, const std::vector<SpotLight>& spotLights) const override;
};

class PhongShader : public Shader
{
public:
    PhongShader();
    void setLighting(const std::vector<DirLight>& dirLights, const std::vector<PointLight>& pointLights, const std::vector<SpotLight>& spotLights) const override;
};

class SkyboxShader : public Shader
{
public:
    SkyboxShader();
    void setLighting(const std::vector<DirLight>& dirLights, const std::vector<PointLight>& pointLights, const std::vector<SpotLight>& spotLights) const override;
};