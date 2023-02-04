#pragma once

#include <GLFW/glfw3.h>

#include "repository.hpp"


class Controller
{
public:
	Controller(Repository* repository);
	void moveAll();
	glm::vec3 getPlayerPosition() const;
	static void handleUserInput(GLFWwindow* window, int key, int scancode, int action, int mods);

private:
	Repository* repository;
};