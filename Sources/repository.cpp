#include "repository.hpp"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

Repository::Repository() :
#pragma region model initialization

	playerModel("Models/imperial-star-destroyer/Star_destroyer.obj"),

	staticModels
	{
		//"Models/FullDonut.obj"
		//"Models/Sphere.obj",
		//"Models/backpack/backpack.obj"
		//"Models/x-wing/x-wing-flyingv1.obj"

	},

	aiModels
	{

	},

#pragma endregion

#pragma region light source initialization
	
	// Directional light sources
	dirLights
	{
		//DirLight
		//{
		//	{
		//		vec3(0, 0.1f, 0), vec3(0.2f, 0.6f, 0.2f), vec3(0.2f ,0.6f, 0.2f)
		//		//vec3(0, 0, 0), vec3(0, 0, 0), vec3(0, 0, 0)
		//	},
		//	vec3(0, 0, -2.0f)
		//};

	DirLight
	{
		{
			//vec3(0.1f, 0, 0), vec3(0, 0, 0), vec3(0.2f ,0, 0)
			vec3(0.2f, 0.2f, 0.2f), vec3(0.7f, 0.7f, 0.7f), vec3(0.7f, 0.7f, 0.7f)
		},
		vec3(0, 0, -1.0f)
	}
	},

	// Point light sources
	pointLights
	{
	PointLight
	{
		{
			//vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f), vec3(1.0f ,1.0f, 1.0f)
			vec3(0, 0, 0), vec3(0.8f, 0.3f, 0.3f), vec3(0.8f, 0.3f, 0.3f)
			//vec3(0, 0, 0), vec3(0, 0, 0), vec3(0, 0, 0)
		},
		vec3(0, 1.0f, -1.0f),
	// attenuation
	1.0f,
	0.09f,
	0.032f
	}
	},

	// Spotlights
	spotLights
	{
	SpotLight
	{
		{
			vec3(0, 0, 0), vec3(0.3f, 0.3f, 1), vec3(0.3f, 0.3f, 1)
			//vec3(0, 0, 0), vec3(0, 0, 0), vec3(0, 0, 0)
		},
		vec3(0, 0, -2.0f),
		vec3(0, 0, 1.0f),
	// cut-off
	0.6f,
	0.3f,
	// attenuation
	1.0f,
	0.09f,
	0.032f
	}
	//SpotLight
	//{
	//	{
	//		vec3(0, 0, 0), vec3(0.3f, 0.8f, 0.8f), vec3(0.3f, 0.8f, 0.8f)
	//		//vec3(0, 0, 0), vec3(0, 0, 0), vec3(0, 0, 0)
	//	},
	//	vec3(-1.5f, 0, 0),
	//	vec3(0, 0, 0),
	//	// cut-off
	//	0.91f,
	//	0.82f,
	//	// attenuation
	//	1.0f,
	//	0.7f,
	//	1.8f
	//};
	}
#pragma endregion
	{
		setUpModelInitialPositions();
	}

void Repository::setUpModelInitialPositions()
{
	playerModel.m_model = glm::translate(glm::scale(playerModel.m_model, glm::vec3(0.5f, 0.5f, 0.5f)), glm::vec3(1, 0, 0));
}
