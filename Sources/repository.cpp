#include "repository.hpp"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include "lightattachment.hpp"

Repository::Repository() :
#pragma region model initialization

	playerModel("Models/arc-170/arc170.obj"),

	staticModels
	{
		//"Models/FullDonut.obj"
		//"Models/Sphere.obj",
		//"Models/backpack/backpack.obj"
		//"Models/x-wing/x-wing-flyingv1.obj"
		//"Models/imperial-star-destroyer/Star_destroyer.obj"
		//"Models/venator/source/VenatorLow.fbx"
		"Models/venator2/source/RepublicVenator2.fbx",
		"Models/venator2/source/RepublicVenator2.fbx",
		"Models/lucrehulk/cis_cap_fedcoreship.obj"
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
			vec3(0.3f, 0.2f, 0.1f), vec3(0.85f, 0.55f, 0.4f), vec3(0.85f, 0.85f, 0.85f)
		},
		vec3(0, 0, 1.0f)
	}
	},

	// Point light sources
	pointLights
	{
	// Left venator

	PointLight
	{
		{
			vec3(0, 0, 0), vec3(0.3f, 0.3f, 1.0f), vec3(0.3f, 0.3f, 1.0f)
		},
		vec3(-1270, -1300, -155),
		// attenuation
		1.0f,
		0.001f,
		0.00001f
	},
	PointLight
	{
		{
			vec3(0, 0, 0), vec3(0.3f, 0.3f, 1.0f), vec3(0.3f, 0.3f, 1.0f)
		},
		vec3(-1490, -1165, -155),
		// attenuation
		1.0f,
		0.001f,
		0.00001f
	},
	PointLight
	{
		{
			vec3(0, 0, 0), vec3(0.3f, 0.3f, 1.0f), vec3(0.3f, 0.3f, 1.0f)
		},
		vec3(-1490, -865, -155),
		// attenuation
		1.0f,
		0.001f,
		0.00001f
	},
	PointLight
	{
		{
			vec3(0, 0, 0), vec3(0.3f, 0.3f, 1.0f), vec3(0.3f, 0.3f, 1.0f)
		},
		vec3(-1270, -710, -155),
		// attenuation
		1.0f,
		0.001f,
		0.00001f
	},

	// Right venator

	PointLight
	{
		{
			vec3(0, 0, 0), vec3(0.3f, 0.3f, 1.0f), vec3(0.3f, 0.3f, 1.0f)
		},
		vec3(-1270, 1300, -155),
		// attenuation
		1.0f,
		0.001f,
		0.00001f
	},
	PointLight
	{
		{
			vec3(0, 0, 0), vec3(0.3f, 0.3f, 1.0f), vec3(0.3f, 0.3f, 1.0f)
		},
		vec3(-1490, 1165, -155),
		// attenuation
		1.0f,
		0.001f,
		0.00001f
	},
	PointLight
	{
		{
			vec3(0, 0, 0), vec3(0.3f, 0.3f, 1.0f), vec3(0.3f, 0.3f, 1.0f)
		},
		vec3(-1490, 865, -155),
		// attenuation
		1.0f,
		0.001f,
		0.00001f
	},
	PointLight
	{
		{
			vec3(0, 0, 0), vec3(0.3f, 0.3f, 1.0f), vec3(0.3f, 0.3f, 1.0f)
		},
		vec3(-1270, 710, -155),
		// attenuation
		1.0f,
		0.001f,
		0.00001f
	},

	// Lucrehulk

	PointLight
	{
		{
			vec3(0, 0, 0), vec3(0.3f, 0.3f, 1.0f), vec3(0.3f, 0.3f, 1.0f)
		},
		vec3(6270, -310, -21),
		// attenuation
		1.0f,
		0.001f,
		0.00001f
	},
	PointLight
	{
		{
			vec3(0, 0, 0), vec3(0.3f, 0.3f, 1.0f), vec3(0.3f, 0.3f, 1.0f)
		},
		vec3(6300, -20, -145),
		// attenuation
		1.0f,
		0.001f,
		0.00001f
	},
	PointLight
	{
		{
			vec3(0, 0, 0), vec3(0.3f, 0.3f, 1.0f), vec3(0.3f, 0.3f, 1.0f)
		},
		vec3(6270, 310, -21),
		// attenuation
		1.0f,
		0.001f,
		0.00001f
	}
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
		attachLights();
	}

void Repository::setUpModelInitialPositions()
{
	staticModels[0].setModelMatrix(
		glm::rotate(
			glm::scale(
				glm::translate(
					glm::mat4(1.0f), glm::vec3(0, -1000, 0)),
				glm::vec3(0.1f, 0.1f, 0.1f)),
			glm::pi<float>(), glm::vec3(1, 0, 0))
	);

	staticModels[1].setModelMatrix(
		glm::rotate(
			glm::scale(
				glm::translate(
					glm::mat4(1.0f), glm::vec3(0, 1000, 0)),
				glm::vec3(0.1f, 0.1f, 0.1f)),
			glm::pi<float>(), glm::vec3(1, 0, 0))
	);

	staticModels[2].setModelMatrix(
		glm::rotate(
		glm::rotate(
			glm::scale(
				glm::translate(
					glm::mat4(1.0f), glm::vec3(4000, 0, 0)),
				glm::vec3(300, 300, 300)),
			glm::pi<float>() * 0.5f, glm::vec3(0, 1, 0)),
			glm::pi<float>() * 0.5f, glm::vec3(0, 0, -1))
	);
}

void Repository::attachLights()
{
	SpotLight leftWingLight
	{
		{
			vec3(0, 0, 0), vec3(0.3f, 0.3f, 1), vec3(0.3f, 0.3f, 1)
			//vec3(0, 0, 0), vec3(0, 0, 0), vec3(0, 0, 0)
		},
		vec3(0, 0, 0),
		vec3(1, 0, 0),
		// cut-off
		glm::cos(glm::radians(7.0f)),
		glm::cos(glm::radians(10.0f)),
		// attenuation
		1.0f,
		0.00005f,
		0.000001f
	};
	spotLights.push_back(leftWingLight);
	

	SpotLight rightWingLight
	{
		{
			vec3(0, 0, 0), vec3(0.3f, 0.3f, 1), vec3(0.3f, 0.3f, 1)
			//vec3(0, 0, 0), vec3(0, 0, 0), vec3(0, 0, 0)
		},
		vec3(0, 0, 0),
		vec3(1, 0, 0),
		// cut-off
		glm::cos(glm::radians(7.0f)),
		glm::cos(glm::radians(10.0f)),
		// attenuation
		1.0f,
		0.00005f,
		0.000001f
	};
	spotLights.push_back(rightWingLight);

	// Attach the lights
	playerModel.attachSpotLight(0, -50.0f, 0, &spotLights[spotLights.size() - 2]);
	playerModel.attachSpotLight(0, 50.0f, 0, &spotLights[spotLights.size() - 1]);

	playerModel.updateAttachedLights();
}
