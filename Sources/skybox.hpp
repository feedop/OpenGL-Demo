#pragma once

#include <vector>
#include <memory>

#include "shader.hpp"

class Skybox
{
public:
	Skybox();
	void draw(const std::shared_ptr<Shader> skybox);

private:
	unsigned int VAO, VBO;
	unsigned int cubemapTexture;

	std::vector<float>skyboxVertices;
};