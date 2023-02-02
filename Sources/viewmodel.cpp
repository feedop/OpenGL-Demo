#include "viewmodel.hpp"

#include <glad/glad.h>

ViewModel::ViewModel(Repository* repository) : repository(repository)
{
	// Create shaders
	shaders = {
		std::shared_ptr<Shader>(new SolidColorShader),
		std::shared_ptr<Shader>(new GouraudShader),
		std::shared_ptr<Shader>(new PhongShader)
	};

	skyboxShader = std::shared_ptr<Shader>(new SkyboxShader);

	// Create cameras
	cameras =
	{
		std::shared_ptr<Camera>(new MovableCamera(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1))),
		std::shared_ptr<Camera>(new FollowingCamera(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0, 0, 0))),
		std::shared_ptr<Camera>(new ThirdPersonCamera(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0, 0, 0)))
	};

	// Projection matrix
	m_projection = glm::perspective<float>(90.0f, 1, 0.1f, 20.0f);
}

void ViewModel::draw()
{
	// Get updated view matrix
	m_view = cameras[selectedCamera]->getLookAt();

	// Use the selected shader and provite it with necessary uniforms
	shaders[selectedShader]->use();
	shaders[selectedShader]->setMatrix("u_view", m_view);
	shaders[selectedShader]->setMatrix("u_projection", m_projection);
	shaders[selectedShader]->setVector("viewPos", cameras[selectedCamera]->getCameraPosition());
	shaders[selectedShader]->setLighting(repository->dirLights, repository->pointLights, repository->spotLights);

	// Draw every model
	repository->playerModel.draw(shaders[selectedShader]);

	for (Model model : repository->aiModels)
		model.draw(shaders[selectedShader]);

	for (Model model : repository->staticModels)
		model.draw(shaders[selectedShader]);

	// Draw the background
	glDepthFunc(GL_LEQUAL);
	skyboxShader->use();
	glm::mat4 noTranslationView = glm::mat4(glm::mat3(m_view));
	skyboxShader->setMatrix("u_view", noTranslationView);
	skyboxShader->setMatrix("u_projection", m_projection);

	skybox.draw(skyboxShader);

	glDepthFunc(GL_LESS);
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
