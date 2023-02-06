#pragma once

#include <vector>
#include <memory>
#include <string>
#include <assimp/scene.h>

#include "shader.hpp"
#include "mesh.hpp"
#include "textures/textureloading.hpp"
#include "lightattachment.hpp"

class Model
{
public:
    Model(const char* path);
    
    void draw(const std::shared_ptr<Shader> shader) const;
    void setModelMatrix(glm::mat4 modelMatrix);

protected:
    glm::mat4 modelMatrix = glm::mat4(1.0f);

    std::vector<Texture> textures_loaded;
    std::string directory;
    std::vector<Mesh> meshes;

    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
    
};