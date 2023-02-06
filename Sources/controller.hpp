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
	void adjustParametersUsingInput();

private:
	Repository* repository;

	struct PressedKeys
	{
		bool W = false;
		bool S = false;
		bool A = false;
		bool D = false;
		bool UP = false;
		bool DOWN = false;
		bool LEFT = false;
		bool RIGHT = false;
	} pressedKeys;
};