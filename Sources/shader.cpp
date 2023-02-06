#include "shader.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <format>
#include <string_view>

#include <glad/glad.h> // include glad to get all the required OpenGL headers

std::string getShaderCode(const char* filePath)
{
    std::string shaderCode;
    std::ifstream shaderFile;
    // ensure ifstream objects can throw exceptions:
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        shaderFile.open(filePath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << shaderFile.rdbuf();
        // close file handlers
        shaderFile.close();
        // convert stream into string
        shaderCode = vShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ, path: " << filePath << std::endl;
        exit(1);
    }
    return shaderCode;
}

GLuint compileShader(GLuint type, const char* shaderCode)
{
    int success;
    char infoLog[512];

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderCode, NULL);
    glCompileShader(shader);
    // print compile errors if any
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        exit(1);
    };
    return shader;
}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{ 
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode = getShaderCode(vertexPath);
    std::string fragmentCode = getShaderCode(fragmentPath);

    // 2. compile shaders
    GLuint vertex = compileShader(GL_VERTEX_SHADER, vertexCode.c_str());
    GLuint fragment = compileShader(GL_FRAGMENT_SHADER, fragmentCode.c_str());

    // 3. shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    // print linking errors if any
    int success;
    char infoLog[512];

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // 4. delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);

}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::setFloat(const char* name, float value) const
{
    int location = glGetUniformLocation(ID, name);
    glUniform1f(location, value);
}

void Shader::setInt(const char* name, int value) const
{
    int location = glGetUniformLocation(ID, name);
    glUniform1i(location, value);
}

void Shader::setVector(const char* name, glm::vec3 vector) const
{
    int location = glGetUniformLocation(ID, name);
    glUniform3f(location, vector.x, vector.y, vector.z);
}

void Shader::setMatrix(const char* name, glm::mat4 matrix) const
{
    int location = glGetUniformLocation(ID, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

SolidColorShader::SolidColorShader() : Shader("Shaders\\solidcolor.vert", "Shaders\\solidcolor.frag") {}

void SolidColorShader::setLighting(const std::vector<DirLight>& dirLights, const std::vector<PointLight>& pointLights, const std::vector<SpotLight>& spotLights) const
{}

GouraudShader::GouraudShader() : Shader("Shaders\\gouraud.vert", "Shaders\\gouraud.frag") {}

void GouraudShader::setLighting(const std::vector<DirLight>& dirLights, const std::vector<PointLight>& pointLights, const std::vector<SpotLight>& spotLights) const
{
    // Directional lights
    for (int i = 0; i < dirLights.size(); i++)
    {
        setVector(std::format("dirLights[{}].direction", i).c_str(), dirLights[i].direction);
        setVector(std::format("dirLights[{}].ambient", i).c_str(), dirLights[i].ambient);
        setVector(std::format("dirLights[{}].diffuse", i).c_str(), dirLights[i].diffuse);
        setVector(std::format("dirLights[{}].specular", i).c_str(), dirLights[i].specular);
    }

    // Point lights
    for (int i = 0; i < pointLights.size(); i++)
    {
        setVector(std::format("pointLights[{}].position", i).c_str(), pointLights[i].position);
        setFloat(std::format("pointLights[{}].constant", i).c_str(), pointLights[i].constant);
        setFloat(std::format("pointLights[{}].linear", i).c_str(), pointLights[i].linear);
        setFloat(std::format("pointLights[{}].quadratic", i).c_str(), pointLights[i].quadratic);
        setVector(std::format("pointLights[{}].ambient", i).c_str(), pointLights[i].ambient);
        setVector(std::format("pointLights[{}].diffuse", i).c_str(), pointLights[i].diffuse);
        setVector(std::format("pointLights[{}].specular", i).c_str(), pointLights[i].specular);
    }

    // Spotlight
    for (int i = 0; i < spotLights.size(); i++)
    {
        setVector(std::format("spotLights[{}].position", i).c_str(), spotLights[i].position);
        setVector(std::format("spotLights[{}].direction", i).c_str(), spotLights[i].direction);
        setFloat(std::format("spotLights[{}].cutOff", i).c_str(), spotLights[i].cutOff);
        setFloat(std::format("spotLights[{}].outerCutOff", i).c_str(), spotLights[i].outerCutOff);
        setFloat(std::format("spotLights[{}].constant", i).c_str(), spotLights[i].constant);
        setFloat(std::format("spotLights[{}].linear", i).c_str(), spotLights[i].linear);
        setFloat(std::format("spotLights[{}].quadratic", i).c_str(), spotLights[i].quadratic);
        setVector(std::format("spotLights[{}].ambient", i).c_str(), spotLights[i].ambient);
        setVector(std::format("spotLights[{}].diffuse", i).c_str(), spotLights[i].diffuse);
        setVector(std::format("spotLights[{}].specular", i).c_str(), spotLights[i].specular);
    }

    // Sizes
    setInt("dirLightCount", dirLights.size());
    setInt("pointLightCount", pointLights.size());
    setInt("spotLightCount", spotLights.size());
}

PhongShader::PhongShader(unsigned int gPosition, unsigned int gNormal, unsigned int gAlbedoSpec) : Shader("Shaders\\phong.vert", "Shaders\\phong.frag"),
gPosition(gPosition), gNormal(gNormal), gAlbedoSpec(gAlbedoSpec) {}

void PhongShader::setLighting(const std::vector<DirLight>& dirLights, const std::vector<PointLight>& pointLights, const std::vector<SpotLight>& spotLights) const
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gPosition);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gNormal);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);

    setFloat("shininess", 32.0);

    // Directional lights
    for (int i = 0; i < dirLights.size(); i++)
    {
        setVector(std::format("dirLights[{}].direction", i).c_str(), dirLights[i].direction);
        setVector(std::format("dirLights[{}].ambient", i).c_str(), dirLights[i].ambient);
        setVector(std::format("dirLights[{}].diffuse", i).c_str(), dirLights[i].diffuse);
        setVector(std::format("dirLights[{}].specular", i).c_str(), dirLights[i].specular);
    }

    // Point lights
    for (int i = 0; i < pointLights.size(); i++)
    {
        setVector(std::format("pointLights[{}].position", i).c_str(), pointLights[i].position);
        setFloat(std::format("pointLights[{}].constant", i).c_str(), pointLights[i].constant);
        setFloat(std::format("pointLights[{}].linear", i).c_str(), pointLights[i].linear);
        setFloat(std::format("pointLights[{}].quadratic", i).c_str(), pointLights[i].quadratic);
        setVector(std::format("pointLights[{}].ambient", i).c_str(), pointLights[i].ambient);
        setVector(std::format("pointLights[{}].diffuse", i).c_str(), pointLights[i].diffuse);
        setVector(std::format("pointLights[{}].specular", i).c_str(), pointLights[i].specular);
    }

    // Spotlights
    for (int i = 0; i < spotLights.size(); i++)
    {
        setVector(std::format("spotLights[{}].position", i).c_str(), spotLights[i].position);
        setVector(std::format("spotLights[{}].direction", i).c_str(), spotLights[i].direction);
        setFloat(std::format("spotLights[{}].cutOff", i).c_str(), spotLights[i].cutOff);
        setFloat(std::format("spotLights[{}].outerCutOff", i).c_str(), spotLights[i].outerCutOff);
        setFloat(std::format("spotLights[{}].constant", i).c_str(), spotLights[i].constant);
        setFloat(std::format("spotLights[{}].linear", i).c_str(), spotLights[i].linear);
        setFloat(std::format("spotLights[{}].quadratic", i).c_str(), spotLights[i].quadratic);
        setVector(std::format("spotLights[{}].ambient", i).c_str(), spotLights[i].ambient);
        setVector(std::format("spotLights[{}].diffuse", i).c_str(), spotLights[i].diffuse);
        setVector(std::format("spotLights[{}].specular", i).c_str(), spotLights[i].specular);
    }

    // Sizes
    setInt("dirLightCount", dirLights.size());
    setInt("pointLightCount", pointLights.size());
    setInt("spotLightCount", spotLights.size());
}

void PhongShader::use()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Shader::use();
}

SkyboxShader::SkyboxShader() : Shader("Shaders\\skybox.vert", "Shaders\\skybox.frag") {}

void SkyboxShader::setLighting(const std::vector<DirLight>& dirLights, const std::vector<PointLight>& pointLights, const std::vector<SpotLight>& spotLights) const
{}

GeometryPassShader::GeometryPassShader(unsigned int gBuffer) : Shader("Shaders\\g_buffer.vert", "Shaders\\g_buffer.frag"), gBuffer(gBuffer) {}

void GeometryPassShader::setLighting(const std::vector<DirLight>&dirLights, const std::vector<PointLight>&pointLights, const std::vector<SpotLight>&spotLights) const
{}

void GeometryPassShader::use()
{
    glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Shader::use();
}
