#include "controller.hpp"

#include "presenter.hpp"

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

void Controller::handleUserInput(GLFWwindow * window, int key, int scancode, int action, int mods)
{
    const float speed = 0.2f;
    static float angle = 0;
    Presenter* presenter = static_cast<Presenter*>(glfwGetWindowUserPointer(window));
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        if (presenter->selectedCamera == 0)
        {
            // Move the camera
            switch (key)
            {
                /*case GLFW_KEY_W:
                    pitch += speed;
                    Presenter->rotateCamera(yaw, pitch);
                    break;
                case GLFW_KEY_S:
                    pitch -= speed;
                    Presenter->rotateCamera(yaw, pitch);
                    break;*/
            case GLFW_KEY_A:
                angle += speed;
                presenter->rotateCameraSideways(angle);
                break;
            case GLFW_KEY_D:
                angle -= speed;
                presenter->rotateCameraSideways(angle);
                break;
            }
        }
    }
}

void Controller::diveDown()
{}

void Controller::pullUp()
{}

void Controller::turnLeft()
{}

void Controller::turnRight()
{}

void Controller::increaseVelocity()
{}

void Controller::decreaseVelocity()
{}

void Controller::rollLeft()
{}

void Controller::rollRight()
{}
