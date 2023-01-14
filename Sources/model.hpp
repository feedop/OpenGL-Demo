#pragma once

#include <vector>
#include <string>
#include <assimp/scene.h>

#include "shader.hpp"
#include "mesh.hpp"

class Model
{
public:
    std::vector<Mesh> meshes;
    glm::mat4 m_model = glm::mat4(1.0f);

    Model(const char* path);
    
    void Draw(const Shader* shader);
private:    
    std::vector<Texture> textures_loaded;
    std::string directory;

    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
    unsigned int textureFromFile(const char* path, const std::string& directory);
};