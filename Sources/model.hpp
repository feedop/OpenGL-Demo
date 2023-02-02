#pragma once

#include <vector>
#include <memory>
#include <string>
#include <assimp/scene.h>

#include "shader.hpp"
#include "mesh.hpp"
#include "textures/textureloading.hpp"

class Model
{
public:
    
    glm::mat4 m_model = glm::mat4(1.0f);

    Model(const char* path);
    
    void draw(const std::shared_ptr<Shader> shader) const;
protected:    
    std::vector<Texture> textures_loaded;
    std::string directory;
    std::vector<Mesh> meshes;

    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
    
};