#include "fl_window.hpp"

flWindow::flWindow(int width, int height, std::string windowName) : width(width), height(height), windowName(windowName) {
	initWindow(); //initialize window in the constructor
	logger.information("Window initialized"); //log that the window was initialized
}

void flWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface)
{
	if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
		logger.error("Failed to create window surface");
		logger.runtimeError("Failed to create window surface");
	}
	logger.information("Window surface created");
}

void flWindow::initWindow() {
	glfwInit(); //initialize glfw
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); //tell glfw not to create an opengl context
	window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr); //create the window
	logger.information("Window created"); //log that the window was created
	if (window == nullptr) { //if the window was not created
		logger.error("Failed to create window"); //log that the window was not created
		throw std::runtime_error("Failed to create window"); //throw a runtime error
	}
}

flWindow::~flWindow() {
	glfwDestroyWindow(window); //destroy the window
	glfwTerminate(); //terminate glfw
	logger.information("Window destroyed"); //log that the window was destroyed
}