#include "presenter.hpp"

#include <glad/glad.h>

Presenter::Presenter(Repository* repository) : 
	repository(repository),
	staticCamera(new StaticCamera(glm::vec3(3, 3, 3), glm::vec3(0, 0, 0))),
	followingCamera(new FollowingCamera(glm::vec3(3, 3, 3), glm::vec3(0, 0, 0))),
	thirdPersonCamera(new ThirdPersonCamera(glm::vec3(3, 3, 3), glm::vec3(0, 0, 0)))
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
		staticCamera, followingCamera, thirdPersonCamera
	};

	// Projection matrix
	projectionMatrix = glm::perspective<float>(30.0f, 1, 0.1f, 100.0f);

	// Attach cameras to the player model
	repository->playerModel.attachFollowingCamera(followingCamera);
	repository->playerModel.attachThirdPersonCamera(thirdPersonCamera);
}

void Presenter::draw()
{
	// Get updated view matrix
	viewMatrix = cameras[selectedCamera]->getView();

	// Use the selected shader and provite it with necessary uniforms
	shaders[selectedShader]->use();
	shaders[selectedShader]->setMatrix("viewMatrix", viewMatrix);
	shaders[selectedShader]->setMatrix("projectionMatrix", projectionMatrix);
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
	glm::mat4 noTranslationView = glm::mat4(glm::mat3(viewMatrix));
	skyboxShader->setMatrix("viewMatrix", noTranslationView);
	skyboxShader->setMatrix("projectionMatrix", projectionMatrix);

	skybox.draw(skyboxShader);

	glDepthFunc(GL_LESS);
}