#pragma once

#include "logger.h"
#include <string>
#include <vector>
#include "fl_device.hpp"

struct PipelineConfigInfo {
  VkViewport viewport;
  VkRect2D scissor;
  VkPipelineViewportStateCreateInfo viewportInfo;
  VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
  VkPipelineRasterizationStateCreateInfo rasterizationInfo;
  VkPipelineMultisampleStateCreateInfo multisampleInfo;
  VkPipelineColorBlendAttachmentState colorBlendAttachment;
  VkPipelineColorBlendStateCreateInfo colorBlendInfo;
  VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
  VkPipelineLayout pipelineLayout = nullptr;
  VkRenderPass renderPass = nullptr;
  uint32_t subpass = 0;
};

class FL_Pipeline {
public:
	FL_Pipeline(FLDevice &device,const std::string& vertFilePath, const std::string& fragFilePath, const PipelineConfigInfo& configInfo); // Constructor
	~FL_Pipeline(); // Destructor

	FL_Pipeline(const FL_Pipeline&) = delete; // Copy constructor
	FL_Pipeline& operator=(const FL_Pipeline&) = delete; // Copy assignment operator

	static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height); // Default pipeline config info

	Logger logger; // Logger object

private:
	static std::vector<char> readFile(const std::string& filePath); // Read file

	void createGraphicsPipeline(const std::string& vertFilePath, const std::string& fragFilePath, const PipelineConfigInfo& configInfo); // Create graphics pipeline

	void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule); // Create shader module

	FLDevice& device; // FLDevice object
	VkPipeline graphicsPipeline; // VkPipeline object
	VkShaderModule vertShaderModule; // VkShaderModule object
	VkShaderModule fragShaderModule; // VkShaderModule object

};