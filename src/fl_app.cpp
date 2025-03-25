#include "fl_app.hpp"

void flApp::run() {
	while (!window.shouldClose()) {
		glfwPollEvents(); //poll glfw events
	}
}