#include "repository.hpp"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

Repository::Repository() :
#pragma region model initialization

	playerModel("Models/arc-170/arc170.obj"),

	staticModels
	{
		//"Models/FullDonut.obj"
		//"Models/Sphere.obj",
		//"Models/backpack/backpack.obj"
		//"Models/x-wing/x-wing-flyingv1.obj"
		"Models/imperial-star-destroyer/Star_destroyer.obj"
	},

	aiModels
	{

	},

#pragma endregion

#pragma region light source initialization
	
	// Directional light sources
	dirLights
	// Main sunlight
	{
	DirLight
	{
		{
			//vec3(0.1f, 0, 0), vec3(0, 0, 0), vec3(0.2f ,0, 0)
			vec3(0.3f, 0.2f, 0.1f), vec3(0.7f, 0.4f, 0.15f), vec3(0.7f, 0.7f, 0.7f)
		},
		vec3(0, 0, 1.0f)
	}
	},

	// Point light sources
	pointLights
	{
	//PointLight
	//{
	//	{
	//		//vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f), vec3(1.0f ,1.0f, 1.0f)
	//		vec3(0, 0, 0), vec3(0.8f, 0.3f, 0.3f), vec3(0.8f, 0.3f, 0.3f)
	//		//vec3(0, 0, 0), vec3(0, 0, 0), vec3(0, 0, 0)
	//	},
	//	vec3(0, 1.0f, -1.0f),
	//// attenuation
	//1.0f,
	//0.09f,
	//0.032f
	//}
	},

	// Spotlights
	spotLights
{
	//SpotLight
	//{
	//	{
	//		vec3(0, 0, 0), vec3(0.3f, 0.3f, 1), vec3(0.3f, 0.3f, 1)
	//		//vec3(0, 0, 0), vec3(0, 0, 0), vec3(0, 0, 0)
	//	},
	//	vec3(0, 0, -2.0f),
	//	vec3(0, 0, 1.0f),
	//// cut-off
	//0.6f,
	//0.3f,
	//// attenuation
	//1.0f,
	//0.09f,
	//0.032f
	//}
	}
#pragma endregion
	{
		setUpModelInitialPositions();
	}

void Repository::setUpModelInitialPositions()
{
	staticModels[0].setModelMatrix(
		glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 0.3f, 0.3f)), glm::vec3(0, 0, 2))
	);
}
