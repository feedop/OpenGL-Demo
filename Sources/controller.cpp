#include "controller.hpp"
#include "playermodel.hpp"
#include "aimodel.hpp"

Controller::Controller(Repository* repository) : repository(repository)
{}

void Controller::moveAll()
{
	repository->playerModel.move();

	for (AIModel aiModel : repository->aiModels)
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

    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        switch (key)
        {
            // pitch
            case GLFW_KEY_W:
                controller->repository->playerModel.diveDown();
                break;
            case GLFW_KEY_S:
                controller->repository->playerModel.pullUp();
                break;
            // yaw
            case GLFW_KEY_A:
                controller->repository->playerModel.turnLeft();
                break;
            case GLFW_KEY_D:
                controller->repository->playerModel.turnRight();
                break;
            // velocity
            case GLFW_KEY_UP:
                controller->repository->playerModel.increaseVelocity();
                break;
            case GLFW_KEY_DOWN:
                controller->repository->playerModel.decreaseVelocity();
                break;
            // roll
            case GLFW_KEY_LEFT:
                controller->repository->playerModel.rollLeft();
                break;
            case GLFW_KEY_RIGHT:
                controller->repository->playerModel.rollRight();
                break;
        }
    }
}