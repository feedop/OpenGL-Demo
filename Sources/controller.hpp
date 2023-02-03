#pragma once

#include <GLFW/glfw3.h>

#include "repository.hpp"


class Controller
{
public:
	Controller(Repository* repository);
	void moveAll();
	static void handleUserInput(GLFWwindow* window, int key, int scancode, int action, int mods);
	
	void diveDown();
	void pullUp();
	void turnLeft();
	void turnRight();

	void increaseVelocity();
	void decreaseVelocity();
	void rollLeft();
	void rollRight();

private:
	Repository* repository;
};