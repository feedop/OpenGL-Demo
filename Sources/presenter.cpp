#include "presenter.hpp"

#include <glad/glad.h>
#include <iostream>

Presenter::Presenter(Repository* repository) : 
	repository(repository),
	staticCamera(new StaticCamera(glm::vec3(4000, 0, -1000), glm::vec3(0, 0, 0))),
	followingCamera(new FollowingCamera(glm::vec3(-430, -930, -730), glm::vec3(0, 0, 0))),
	thirdPersonCamera(new ThirdPersonCamera(glm::vec3(50, 50, 0), glm::vec3(0, 0, 0))),
	dirLightAmbient(repository->dirLights[0].ambient),
	dirLightDiffuse(repository->dirLights[0].diffuse),
	dirLightSpecular(repository->dirLights[0].specular)	
{

	// Set up OpenGL frame buffers
	glGenFramebuffers(1, &gBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
	unsigned int gPosition, gNormal, gAlbedoSpec;
	// position color buffer
	glGenTextures(1, &gPosition);
	glBindTexture(GL_TEXTURE_2D, gPosition);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, 900, 900, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);
	// normal color buffer
	glGenTextures(1, &gNormal);
	glBindTexture(GL_TEXTURE_2D, gNormal);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, 900, 900, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);
	// color + specular color buffer
	glGenTextures(1, &gAlbedoSpec);
	glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 900, 900, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedoSpec, 0);
	// tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 
	unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	glDrawBuffers(3, attachments);
	// create and attach depth buffer (renderbuffer)
	unsigned int rboDepth;
	glGenRenderbuffers(1, &rboDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 900, 900);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
	// finally check if framebuffer is complete
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Create shaders
	shaders = {
		std::shared_ptr<Shader>(new SolidColorShader),
		std::shared_ptr<Shader>(new GouraudShader),
		std::shared_ptr<Shader>(new GeometryPassShader(gBuffer)),
		std::shared_ptr<Shader>(new PhongShader(gPosition, gNormal, gAlbedoSpec))
	};

	skyboxShader = std::shared_ptr<Shader>(new SkyboxShader);

	// Configure the lighting pass shader (phong)
	shaders[3]->use();
	shaders[3]->setInt("gPosition", 0);
	shaders[3]->setInt("gNormal", 1);
	shaders[3]->setInt("gAlbedoSpec", 2);

	// Create cameras
	cameras =
	{
		staticCamera, followingCamera, thirdPersonCamera
	};

	// Attach cameras to the player model
	repository->playerModel.attachFollowingCamera(followingCamera);
	repository->playerModel.attachThirdPersonCamera(thirdPersonCamera);
}

void Presenter::draw()
{
	// Get updated view matrix
	glm::mat4 viewMatrix = cameras[selectedCamera]->getView(invertThirdPersonCamera);
	glm::mat4 projectionMatrix = cameras[selectedCamera]->getProjection();

	// Use the selected shader and provite it with necessary uniforms
	shaders[selectedShader]->use();
	shaders[selectedShader]->setMatrix("viewMatrix", viewMatrix);
	shaders[selectedShader]->setMatrix("projectionMatrix", projectionMatrix);
	shaders[selectedShader]->setVector("viewPos", cameras[selectedCamera]->getCameraPosition());
	shaders[selectedShader]->setVector("fog.color", fogColor);
	shaders[selectedShader]->setFloat("fog.density", fogDensity);
	shaders[selectedShader]->setLighting(repository->dirLights, repository->pointLights, repository->spotLights);

	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);

	// Draw every model
	repository->playerModel.draw(shaders[selectedShader]);

	for (Model& model : repository->aiModels)
		model.draw(shaders[selectedShader]);

	for (Model& model : repository->staticModels)
		model.draw(shaders[selectedShader]);

	// Phong shaders uses deferred shading so it needs an additional pass
	if (selectedShader == 2)
	{
		//glDepthMask(GL_FALSE);
		glDisable(GL_DEPTH_TEST);

		shaders[3]->use();
		shaders[selectedShader]->setVector("viewPos", cameras[selectedCamera]->getCameraPosition());
		shaders[selectedShader]->setVector("fog.color", fogColor);
		shaders[selectedShader]->setFloat("fog.density", fogDensity);
		shaders[3]->setLighting(repository->dirLights, repository->pointLights, repository->spotLights);

		// copy content of geometry's depth buffer to default framebuffer's depth buffer
		// ----------------------------------------------------------------------------------
		glBindFramebuffer(GL_READ_FRAMEBUFFER, gBuffer);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // write to default framebuffer
		// blit to default framebuffer. Note that this may or may not work as the internal formats of both the FBO and default framebuffer have to match.
		// the internal formats are implementation defined. This works on all of my systems, but if it doesn't on yours you'll likely have to write to the 		
		// depth buffer in another shader stage (or somehow see to match the default framebuffer's internal format with the FBO's internal format).
		glBlitFramebuffer(0, 0, 900, 900, 0, 0, 900, 900, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// Render quad
		unsigned int quadVAO = 0;
		unsigned int quadVBO = 0;

		float quadVertices[] = {
			// positions        // texture Coords
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
				1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
				1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};
		// setup plane VAO
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glBindVertexArray(quadVAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);

		
	}
	// Draw the background
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	skyboxShader->use();
	glm::mat4 noTranslationView = glm::mat4(glm::mat3(viewMatrix));
	skyboxShader->setMatrix("viewMatrix", noTranslationView);
	skyboxShader->setMatrix("projectionMatrix", projectionMatrix);
	skyboxShader->setVector("fog.color", fogColor);
	skyboxShader->setFloat("fog.density", fogDensity);

	skybox.draw(skyboxShader);

	glDepthFunc(GL_LESS);
}

void Presenter::countFramesForNight()
{
	if (night && nightFrames < maxFrames)
	{
		repository->dirLights[0].diffuse -= frameCoefficient * (dirLightDiffuse - dirLightAmbient);
		repository->dirLights[0].specular -= frameCoefficient * (dirLightSpecular - dirLightAmbient);
		nightFrames++;
	}
	else if (!night && nightFrames > 0)
	{
		repository->dirLights[0].diffuse += frameCoefficient * (dirLightDiffuse - dirLightAmbient);
		repository->dirLights[0].specular += frameCoefficient * (dirLightSpecular -dirLightAmbient);
		nightFrames--;
	}
}
