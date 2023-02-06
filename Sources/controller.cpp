#include "controller.hpp"
#include "playermodel.hpp"
#include "aimodel.hpp"

Controller::Controller(Repository* repository) : repository(repository)
{}

void Controller::moveAll()
{
	repository->playerModel.move();

	for (AIModel& aiModel : repository->aiModels)
	{
		aiModel.move();
	}
}

glm::vec3 Controller::getPlayerPosition() const
{
    return repository->playerModel.getPosition();
}

// Handle keyboard input by rotating the player model
void Controller::handleUserInput(GLFWwindow * window, int key, int scancode, int action, int mods)
{
    Controller* controller = static_cast<Controller*>(glfwGetWindowUserPointer(window));

    if (action == GLFW_PRESS)
    {
        switch (key)
        {
            // pitch
            case GLFW_KEY_W:
                controller->pressedKeys.W = true;
                break;
            case GLFW_KEY_S:
                controller->pressedKeys.S = true;
                break;
            // yaw
            case GLFW_KEY_A:
                controller->pressedKeys.A = true;
                break;
            case GLFW_KEY_D:
                controller->pressedKeys.D = true;
                break;
            // velocity
            case GLFW_KEY_UP:
                controller->pressedKeys.UP = true;
                break;
            case GLFW_KEY_DOWN:
                controller->pressedKeys.DOWN = true;
                break;
            // roll
            case GLFW_KEY_LEFT:
                controller->pressedKeys.LEFT = true;;
                break;
            case GLFW_KEY_RIGHT:
                controller->pressedKeys.RIGHT = true;
                break;
        }
    }
	else if (action == GLFW_RELEASE)
	{
		switch (key)
		{
			// pitch
		case GLFW_KEY_W:
			controller->pressedKeys.W = false;
			break;
		case GLFW_KEY_S:
			controller->pressedKeys.S = false;
			break;
			// yaw
		case GLFW_KEY_A:
			controller->pressedKeys.A = false;
			break;
		case GLFW_KEY_D:
			controller->pressedKeys.D = false;
			break;
			// velocity
		case GLFW_KEY_UP:
			controller->pressedKeys.UP = false;
			break;
		case GLFW_KEY_DOWN:
			controller->pressedKeys.DOWN = false;
			break;
			// roll
		case GLFW_KEY_LEFT:
			controller->pressedKeys.LEFT = false;
			break;
		case GLFW_KEY_RIGHT:
			controller->pressedKeys.RIGHT = false;
			break;
		}
	}
}

void Controller::adjustParametersUsingInput()
{
    if (pressedKeys.W)
        repository->playerModel.diveDown();
    if (pressedKeys.S)
        repository->playerModel.pullUp();
    if (pressedKeys.A)
        repository->playerModel.turnLeft();
    if (pressedKeys.D)
        repository->playerModel.turnRight();
    if (pressedKeys.UP)
        repository->playerModel.increaseVelocity();
    if (pressedKeys.DOWN)
        repository->playerModel.decreaseVelocity();
    if (pressedKeys.LEFT)
        repository->playerModel.rollLeft();
    if (pressedKeys.RIGHT)
        repository->playerModel.rollRight();
}
