#pragma once

#include <vector>
#include <string>

namespace stbi
{
	void flipVertically();

	unsigned int textureFromFile(const char* path, const std::string& directory);

	unsigned int loadCubemap(const std::vector<std::string>& faces);
}