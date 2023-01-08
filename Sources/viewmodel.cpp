#include "viewmodel.hpp"

ViewModel::ViewModel()
{
	models =
	{
		"Models/FullDonut.obj"
	};

	Shader solidColorShader("Shaders\\solidcolor.vert", "Shaders\\solidcolor.frag");
	Shader gourardShader("Shaders\\solidcolor.vert", "Shaders\\solidcolor.frag");
	Shader phongShader("Shaders\\solidcolor.vert", "Shaders\\solidcolor.frag");

	shaders.push_back(solidColorShader);
	shaders.push_back(gourardShader);
	shaders.push_back(phongShader);
}

void ViewModel::Draw()
{
	shaders[selectedShader].use();
	shaders[selectedShader].setMatrix("u_view", m_view);
	shaders[selectedShader].setMatrix("u_projection", m_projection);
	shaders[selectedShader].setVector("u_lightColor", m_lightColor);

	for (unsigned int i = 0; i < models.size(); i++)
		models[i].Draw(shaders[selectedShader]);
}
