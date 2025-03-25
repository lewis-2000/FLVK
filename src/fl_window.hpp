#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>
#include "logger.h"

class flWindow {
public:
	flWindow(int width, int height, std::string windowName); //constructor
	~flWindow(); //destructor
	Logger logger; //logger object

	flWindow(const flWindow&) = delete; //copy constructor
	flWindow& operator=(const flWindow&) = delete; //copy assignment operator

	bool shouldClose() { return glfwWindowShouldClose(window); } //check if the window should close

	void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface); //create window surface

private:
	void initWindow(); //initialize window
	const int width; //window width
	const int height; //window height

	std::string windowName; //window name
	GLFWwindow* window; //glfw window


};