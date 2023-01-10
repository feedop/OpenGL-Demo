#pragma once

#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include "shader.hpp"
#include "material.hpp"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

class Mesh {
public:
    // mesh data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    glm::mat4 m_model = glm::mat4(1.0f);

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material material = Material::whitePlastic());
    void Draw(const Shader* shader);
private:
    Material material;
    //  render data
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};