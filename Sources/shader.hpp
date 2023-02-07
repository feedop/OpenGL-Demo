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
    void setFloat(const char* name, float value) const;
    void setInt(const char* name, int value) const;
    void setVector(const char* name, glm::vec3 vector) const;
    void setMatrix(const char* name, glm::mat4 matrix) const;
    virtual void setLighting(const std::vector<DirLight>& dirLights, const std::vector<PointLight>& pointLights, const std::vector<SpotLight>& spotLights) const;
protected:
    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
};

class SolidColorShader : public Shader
{
public:
    SolidColorShader();
};

class GouraudShader : public Shader
{
public:
    GouraudShader();
    void setLighting(const std::vector<DirLight>& dirLights, const std::vector<PointLight>& pointLights, const std::vector<SpotLight>& spotLights) const override;
};

class GeometryPassShader : public Shader
{
public:
    GeometryPassShader(unsigned int gBuffer);
    void use() override;
private:
    unsigned int gBuffer;
};

class PhongShader : public Shader
{
public:
    PhongShader(unsigned int gPosition, unsigned int gNormal, unsigned int gAlbedoSpec);
    void setLighting(const std::vector<DirLight>& dirLights, const std::vector<PointLight>& pointLights, const std::vector<SpotLight>& spotLights) const override;
    void use() override;
private:
    unsigned int gPosition;
    unsigned int gNormal;
    unsigned int gAlbedoSpec;
};

class SkyboxShader : public Shader
{
public:
    SkyboxShader();
};