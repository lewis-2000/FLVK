#pragma once

#include "fl_window.hpp"
#include "fl_pipeline.hpp"
#include "fl_device.hpp"

class flApp {
public:
	static constexpr int WIDTH = 800; //constexpr width
	static constexpr int HEIGHT = 600; //constexpr height

	void run(); //run the app

private:
	flWindow window{ WIDTH,HEIGHT,"FLEngine Vulkan" }; //window object
	FLDevice device{ window };
	FL_Pipeline pipeline{ device,"simple_shader.vert.spv","simple_shader.frag.spv", FL_Pipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)}; //pipeline objectipeline{ "shaders/simple_shader.vert.spv","shaders/simple_shader.frag.spv" }; //pipeline object
};