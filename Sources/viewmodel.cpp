#include "viewmodel.hpp"

ViewModel::ViewModel()
{
	// Create models
	models =
	{
		//"Models/FullDonut.obj"
		//"Models/Sphere.obj",
		"Models/backpack/backpack.obj"
		//"Models/x-wing/x-wing-flyingv1.obj"
	};

	// Create shaders
	shaders = {
		new SolidColorShader,
		new GouraudShader,
		new PhongShader
	};

	// Create cameras
	cameras =
	{
		new MovableCamera(glm::vec3(3.0f, 1.0f, 3.0f), glm::vec3(0, 0, 0)),
		new FollowingCamera(glm::vec3(3.0f, 0, 3.0f), glm::vec3(0, 0, 0)),
		new ThirdPersonCamera(glm::vec3(3.0f, 0, 3.0f), glm::vec3(0, 0, 0))
	};

	// Projection matrix
	m_projection = glm::perspective<float>(90.0f, 1, 0.1f, 20.0f);

	// Create light sources
	setUpLightSources();
}

ViewModel::~ViewModel()
{
	delete shaders[0];
	delete shaders[1];
	delete shaders[2];
}

void ViewModel::Draw()
{
	// Get updated view matrix
	m_view = cameras[selectedCamera]->getLookAt();

	// Use the selected shader and provite it with necessary uniforms
	shaders[selectedShader]->use();
	shaders[selectedShader]->setMatrix("u_view", m_view);
	shaders[selectedShader]->setMatrix("u_projection", m_projection);
	shaders[selectedShader]->setVector("viewPos", cameras[selectedCamera]->getCameraPosition());
	shaders[selectedShader]->setLighting(dirLights, pointLights, spotLights);

	// Draw every models
	for (Model model : models)
		model.Draw(shaders[selectedShader]);
}

void ViewModel::updateCamera(glm::vec3 position, glm::vec3 front)
{
	cameras[selectedCamera]->updateCamera(position, front);
}

//void ViewModel::rotateCameraUpDown(float pitch)
//{
//	glm::vec3 cameraPosition = cameras[selectedCamera]->getCameraPosition();
//	float radius = cameras[selectedCamera]->getDistanceToTarget();
//	float camZ = radius * glm::cos(pitch);
//	float camY = radius * glm::sin(pitch);
//	/*float camY = cameraPosition.y + pitch;
//	float camZ = cameraPosition.z + pitch;*/
//
//	cameras[selectedCamera]->updateCamera(glm::vec3(cameraPosition.x, camY, camZ), glm::vec3(0, 0, 0));
//}

void ViewModel::rotateCameraSideways(float angle)
{
	glm::vec3 cameraPosition = cameras[selectedCamera]->getCameraPosition();
	glm::vec3 targetPosition = cameras[selectedCamera]->getTargetPosition();
	glm::vec3 centerPosition = glm::vec3(targetPosition.x, cameraPosition.y, targetPosition.z);
	float radius = glm::length(centerPosition - cameraPosition);

	float camX = radius * glm::sin(angle);
	float camZ = radius * glm::cos(angle);

	cameras[selectedCamera]->updateCamera(glm::vec3(camX, cameraPosition.y, camZ), glm::vec3(0, 0, 0));
}

void ViewModel::setUpLightSources()
{
	// Directional light sources
	//DirLight dirLight0
	//{
	//	{
	//		vec3(0, 0.1f, 0), vec3(0.2f, 0.6f, 0.2f), vec3(0.2f ,0.6f, 0.2f)
	//		//vec3(0, 0, 0), vec3(0, 0, 0), vec3(0, 0, 0)
	//	},
	//	vec3(0, 0, -2.0f)
	//};
	//dirLights.push_back(dirLight0);

	DirLight dirLight1
	{
		{
			//vec3(0.1f, 0, 0), vec3(0, 0, 0), vec3(0.2f ,0, 0)
			vec3(0.2f, 0.2f, 0.2f), vec3(0.7f, 0.7f, 0.7f), vec3(0.7f, 0.7f, 0.7f)
		},
		vec3(0, 0, -1.0f)
	};
	dirLights.push_back(dirLight1);

	// Point light sources
	PointLight pointLight0
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
	};
	pointLights.push_back(pointLight0);

	// Spotlights
	SpotLight spotLight0
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
	};
	spotLights.push_back(spotLight0);

	//SpotLight spotLight1
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
	//spotLights.push_back(spotLight1);
}
