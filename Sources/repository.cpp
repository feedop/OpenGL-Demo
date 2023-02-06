#include "repository.hpp"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include "lightattachment.hpp"

Repository::Repository() :
#pragma region model initialization

	playerModel("Models/arc-170/arc170.obj"),

	staticModels
	{
		//"Models/x-wing/x-wing-flyingv1.obj"
		//"Models/imperial-star-destroyer/Star_destroyer.obj"
		//"Models/venator/source/VenatorLow.fbx"
		"Models/venator2/source/RepublicVenator2.fbx",
		"Models/venator2/source/RepublicVenator2.fbx",
		"Models/lucrehulk/cis_cap_fedcoreship.obj"
	},

	aiModels
	{
		"Models/tri-fighter/source/Tri_Fighter.obj",
		"Models/tri-fighter/source/Tri_Fighter.obj",
		"Models/tri-fighter/source/Tri_Fighter.obj"
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

		// create a phase difference
		aiModels[1].rotate(0.1f);
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

	aiModels[0].setRotationMatrix(
		glm::scale(
			glm::rotate(
				glm::translate(
					glm::mat4(1.0f), glm::vec3(1200, 0 ,0)),
				glm::pi<float>() * 0.5f, glm::vec3(-1, 0, 0)),
			glm::vec3(0.3f, 0.3f, 0.3f))
	);
	aiModels[0].setParameters(0.02f, glm::vec3(1500, 0, -200), glm::vec3(0, 0, -1));
	aiModels[0].rotateInitialCoordinateSystem(glm::pi<float>() * 0.5f);

	aiModels[1].setRotationMatrix(
		glm::scale(
			glm::rotate(
				glm::translate(
					glm::mat4(1.0f), glm::vec3(1000, 0, 0)),
				glm::pi<float>() * 0.5f, glm::vec3(-1, 0, 0)),
			glm::vec3(0.3f, 0.3f, 0.3f))
	);
	aiModels[1].setParameters(0.02f, glm::vec3(1500, 0, -200), glm::vec3(0, 0, -1));
	aiModels[1].rotateInitialCoordinateSystem(glm::pi<float>() * 0.5f);

	aiModels[2].setRotationMatrix(
		glm::scale(
			glm::rotate(
				glm::translate(
					glm::mat4(1.0f), glm::vec3(800, 0, 0)),
				glm::pi<float>() * 0.5f, glm::vec3(-1, 0, 0)),
			glm::vec3(0.3f, 0.3f, 0.3f))
	);
	aiModels[2].setParameters(0.02f, glm::vec3(1500, 0, -200), glm::vec3(0, 0, -1));
	aiModels[2].rotateInitialCoordinateSystem(glm::pi<float>() * 0.5f);
}

void Repository::attachLights()
{
#pragma region player model
	// Spotlights
	// 
	// arc-170 left wing light
	spotLights.emplace_back(
		SpotLight
		{
			{
				vec3(0, 0, 0), vec3(0.3f, 0.3f, 1), vec3(0.3f, 0.3f, 1)
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
		}
	);
	
	// arc-170 right wing light
	spotLights.emplace_back(
		SpotLight
		{
			{
				vec3(0, 0, 0), vec3(0.3f, 0.3f, 1), vec3(0.3f, 0.3f, 1)
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
		}
	);

	// arc-170 engine left light
	spotLights.emplace_back(
		SpotLight
		{
			{
				vec3(0, 0, 0), vec3(1, 0.3f, 1), vec3(1, 0.3f, 1)
			},
			vec3(0, 0, 0),
			vec3(1, 0, 0),
		// cut-off
		glm::cos(glm::radians(8.0f)),
		glm::cos(glm::radians(15.0f)),
		// attenuation
		1.0f,
		0.0001f,
		0.000001f
		}
	);

	// arc-170 engine right light
	spotLights.emplace_back(
		SpotLight
		{
			{
				vec3(0, 0, 0), vec3(1, 0.3f, 1), vec3(1, 0.3f, 1)
			},
			vec3(0, 0, 0),
			vec3(1, 0, 0),
		// cut-off
		glm::cos(glm::radians(8.0f)),
		glm::cos(glm::radians(15.0f)),
		// attenuation
		1.0f,
		0.0001f,
		0.000001f
		}
	);

	// Point lights
	//PointLight arcEngineLight
	//{
	//	{
	//		vec3(0, 0, 0), vec3(1.0f, 0.3f, 1.0f), vec3(1.0f, 0.3f, 1.0f)
	//	},
	//	vec3(0, 0, 0),
	//	// attenuation
	//	1.0f,
	//	0.001f,
	//	0.00001f
	//};
	//pointLights.push_back(arcEngineLight);
	//playerModel.attachPointLight(-10.0f, 0, 0, &pointLights[spotLights.size() - 1]);

#pragma endregion

#pragma region ai models
	// tri-gun 0 front
	spotLights.emplace_back(
		SpotLight
		{
			{
				vec3(0, 0, 0), vec3(0.3f, 0.3f, 1), vec3(0.3f, 0.3f, 1)
			},
			vec3(0, 0, 0),
			vec3(1, 0, 0),
		// cut-off
		glm::cos(glm::radians(12.5f)),
		glm::cos(glm::radians(25.0f)),
		// attenuation
		1.0f,
		0.00005f,
		0.000001f
		}
	);
	//tri-gun 0 back
	spotLights.emplace_back(
		SpotLight
		{
			{
				vec3(0, 0, 0), vec3(1, 0.3f, 0.3f), vec3(1, 0.3f, 0.3f)
			},
			vec3(0, 0, 0),
			vec3(1, 0, 0),
		// cut-off
		glm::cos(glm::radians(12.5f)),
		glm::cos(glm::radians(25.0f)),
		// attenuation
		1.0f,
		0.00005f,
		0.000001f
		}
	);
	// tri-gun 1 front
	spotLights.emplace_back(
		SpotLight
		{
			{
				vec3(0, 0, 0), vec3(0.3f, 0.3f, 1), vec3(0.3f, 0.3f, 1)
			},
			vec3(0, 0, 0),
			vec3(1, 0, 0),
		// cut-off
		glm::cos(glm::radians(12.5f)),
		glm::cos(glm::radians(25.0f)),
		// attenuation
		1.0f,
		0.00005f,
		0.000001f
		}
	);
	//tri-gun 1 back
	spotLights.emplace_back(
		SpotLight
		{
			{
				vec3(0, 0, 0), vec3(1, 0.3f, 0.3f), vec3(1, 0.3f, 0.3f)
			},
			vec3(0, 0, 0),
			vec3(1, 0, 0),
		// cut-off
		glm::cos(glm::radians(12.5f)),
		glm::cos(glm::radians(25.0f)),
		// attenuation
		1.0f,
		0.00005f,
		0.000001f
		}
	);
	// tri-gun 2 front
	spotLights.emplace_back(
		SpotLight
		{
			{
				vec3(0, 0, 0), vec3(0.3f, 0.3f, 1), vec3(0.3f, 0.3f, 1)
			},
			vec3(0, 0, 0),
			vec3(1, 0, 0),
		// cut-off
		glm::cos(glm::radians(12.5f)),
		glm::cos(glm::radians(25.0f)),
		// attenuation
		1.0f,
		0.00005f,
		0.000001f
		}
	);
	//tri-gun 2 back
	spotLights.emplace_back(
		SpotLight
		{
			{
				vec3(0, 0, 0), vec3(1, 0.3f, 0.3f), vec3(1, 0.3f, 0.3f)
			},
			vec3(0, 0, 0),
			vec3(1, 0, 0),
		// cut-off
		glm::cos(glm::radians(12.5f)),
		glm::cos(glm::radians(25.0f)),
		// attenuation
		1.0f,
		0.00005f,
		0.000001f
		}
	);
#pragma endregion

#pragma region attaching and updating

	// Attach the lights

	int i = spotLights.size() - 10;

	playerModel.attachSpotLight(0, -30.0f, 0, &spotLights[i++]);
	playerModel.attachSpotLight(0, 30.0f, 0, &spotLights[i++]);
	playerModel.attachSpotLight(-5.0f, -30.0f, 0, &spotLights[i++], true);
	playerModel.attachSpotLight(-5.0f, 30.0f, 0, &spotLights[i++], true);

	aiModels[0].attachSpotLight(0, 0, 0, &spotLights[i++]);
	aiModels[0].attachSpotLight(0, 0, 0, &spotLights[i++], true);
	aiModels[1].attachSpotLight(0, 0, 0, &spotLights[i++]);
	aiModels[1].attachSpotLight(0, 0, 0, &spotLights[i++], true);
	aiModels[2].attachSpotLight(0, 0, 0, &spotLights[i++]);
	aiModels[2].attachSpotLight(0, 0, 0, &spotLights[i++], true);

	// Update

	playerModel.updateAttachedLights();

	for (auto& aiModel : aiModels)
	{
		aiModel.updateAttachedLights();
	}

#pragma endregion
}
