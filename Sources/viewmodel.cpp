#include "viewmodel.hpp"

ViewModel::ViewModel()
{
	// Create models
	models =
	{
		//"Models/FullDonut.obj"
		"Models/Sphere.obj",
	};

	// Create shaders

	shaders.push_back(new SolidColorShader);
	shaders.push_back(new GouraudShader);
	shaders.push_back(new PhongShader);

	// Create light sources

	// Directional light sources
	DirLight dirLight0
	{
		{
			vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f), vec3(1.0f ,1.0f, 1.0f)
			//vec3(0, 0, 0), vec3(0, 0, 0), vec3(0, 0, 0)
		},
		vec3(0, 0, -1.0f)
	};
	dirLights.push_back(dirLight0);

	// Point light sources
	PointLight pointLight0
	{
		{
			//vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f), vec3(1.0f ,1.0f, 1.0f)
			vec3(1.0f, 0.3f, 0.3f), vec3(1.0f, 0.3f, 0.3f), vec3(1.0f, 0.3f, 0.3f)
			//vec3(0, 0, 0), vec3(0, 0, 0), vec3(0, 0, 0)
		},
		vec3(0, 0.2f, 1.5f),
		// attenuation
		1.0f,
		0.22f,
		0.2f
	};
	pointLights.push_back(pointLight0);

	// Spotlights
	SpotLight spotLight0
	{
		{
			vec3(0.3f, 0.3f, 1.0f), vec3(0.3f, 0.3f, 1.0f), vec3(0.3f, 0.3f, 1.0f)
			//vec3(0, 0, 0), vec3(0, 0, 0), vec3(0, 0, 0)
		},
		vec3(0.2f, 0, 0.2f),
		vec3(0, 0, 0.1f),
		// cut-off
		0.91f,
		0.82f,
		// attenuation
		1.0f,
		0.7f,
		1.8f
	};
	spotLights.push_back(spotLight0);

	SpotLight spotLight1
	{
		{
			//vec3(0.3f, 0.3f, 1.0f), vec3(0.3f, 0.3f, 1.0f), vec3(0.3f, 0.3f, 1.0f)
			vec3(0, 0, 0), vec3(0, 0, 0), vec3(0, 0, 0)
		},
		vec3(-1.5f, 0, 0),
		vec3(0, 0, 0),
		// cut-off
		0.91f,
		0.82f,
		// attenuation
		1.0f,
		0.7f,
		1.8f
	};
	spotLights.push_back(spotLight1);
}

ViewModel::~ViewModel()
{
	delete shaders[0];
	delete shaders[1];
	delete shaders[2];
}

void ViewModel::Draw()
{
	shaders[selectedShader]->use();
	shaders[selectedShader]->setMatrix("u_view", m_view);
	shaders[selectedShader]->setMatrix("u_projection", m_projection);
	shaders[selectedShader]->setLighting(dirLights, pointLights, spotLights);

	for (unsigned int i = 0; i < models.size(); i++)
		models[i].Draw(shaders[selectedShader]);
}
