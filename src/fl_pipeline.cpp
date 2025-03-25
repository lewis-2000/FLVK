#include "fl_pipeline.hpp"
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <cassert>

FL_Pipeline::FL_Pipeline(FLDevice& device, const std::string& vertFilePath, const std::string& fragFilePath, const PipelineConfigInfo& configInfo) : device(device)
{
	createGraphicsPipeline(vertFilePath, fragFilePath, configInfo); // Create the graphics pipeline
}

FL_Pipeline::~FL_Pipeline()
{
	vkDestroyShaderModule(device.device(), vertShaderModule, nullptr); // Destroy the vertex shader module
	vkDestroyShaderModule(device.device(), fragShaderModule, nullptr); // Destroy the fragment shader module
	vkDestroyPipeline(device.device(), graphicsPipeline, nullptr); // Destroy the graphics pipeline
}

PipelineConfigInfo FL_Pipeline::defaultPipelineConfigInfo(uint32_t width, uint32_t height)
{
	PipelineConfigInfo configInfo = {}; // Create a pipeline config info struct
	configInfo.inputAssemblyInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO; // Set the type of the struct
	configInfo.inputAssemblyInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST; // Set the topology
	configInfo.inputAssemblyInfo.primitiveRestartEnable = VK_FALSE; // Set the primitive restart enable
	
	configInfo.viewport.x = 0.0f; // Set the x value of the viewport
	configInfo.viewport.y = 0.0f; // Set the y value of the viewport
	configInfo.viewport.width = static_cast<float>(width); // Set the width of the viewport
	configInfo.viewport.height = static_cast<float>(height); // Set the height of the viewport
	configInfo.viewport.minDepth = 0.0f; // Set the min depth of the viewport
	configInfo.viewport.maxDepth = 1.0f; // Set the max depth of the viewport

	configInfo.scissor.offset = { 0, 0 }; // Set the offset of the scissor
	configInfo.scissor.extent = { width, height }; // Set the extent of the scissor

	configInfo.viewportInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO; // Set the type of the struct
	configInfo.viewportInfo.viewportCount = 1; // Set the viewport count
	configInfo.viewportInfo.pViewports = &configInfo.viewport; // Set the viewports
	configInfo.viewportInfo.scissorCount = 1; // Set the scissor count
	configInfo.viewportInfo.pScissors = &configInfo.scissor; // Set the scissors

	configInfo.rasterizationInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO; // Set the type of the struct
	configInfo.rasterizationInfo.depthClampEnable = VK_FALSE; // Set the depth clamp enable
	configInfo.rasterizationInfo.rasterizerDiscardEnable = VK_FALSE; // Set the rasterizer discard enable
	configInfo.rasterizationInfo.polygonMode = VK_POLYGON_MODE_FILL; // Set the polygon mode
	configInfo.rasterizationInfo.lineWidth = 1.0f;	// Set the line width
	configInfo.rasterizationInfo.cullMode = VK_CULL_MODE_NONE; // Set the cull mode
	configInfo.rasterizationInfo.frontFace = VK_FRONT_FACE_CLOCKWISE; // Set the front face
	configInfo.rasterizationInfo.depthBiasEnable = VK_FALSE; // Set the depth bias enable
	configInfo.rasterizationInfo.depthBiasConstantFactor = 0.0f;  // Optional
	configInfo.rasterizationInfo.depthBiasClamp = 0.0f;           // Optional
	configInfo.rasterizationInfo.depthBiasSlopeFactor = 0.0f;     // Optional

	configInfo.multisampleInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO; // Set the type of the struct
	configInfo.multisampleInfo.sampleShadingEnable = VK_FALSE; // Set the sample shading enable
	configInfo.multisampleInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT; // Set the rasterization samples
	configInfo.multisampleInfo.minSampleShading = 1.0f;           // Optional
	configInfo.multisampleInfo.pSampleMask = nullptr;             // Optional
	configInfo.multisampleInfo.alphaToCoverageEnable = VK_FALSE;  // Optional
	configInfo.multisampleInfo.alphaToOneEnable = VK_FALSE;       // Optional

	configInfo.colorBlendAttachment.colorWriteMask =
		VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT |
		VK_COLOR_COMPONENT_A_BIT; // Set the color write mask
	configInfo.colorBlendAttachment.blendEnable = VK_FALSE; // Set the blend enable
	configInfo.colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;   // Optional
	configInfo.colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;  // Optional
	configInfo.colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;              // Optional
	configInfo.colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;   // Optional
	configInfo.colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;  // Optional
	configInfo.colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;              // Optional
    
	configInfo.colorBlendInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO; // Set the type of the struct
	configInfo.colorBlendInfo.logicOpEnable = VK_FALSE; // Set the logic op enable
	configInfo.colorBlendInfo.logicOp = VK_LOGIC_OP_COPY;  // Optional
	configInfo.colorBlendInfo.attachmentCount = 1; // Set the attachment count
	configInfo.colorBlendInfo.pAttachments = &configInfo.colorBlendAttachment; // Set the attachments
	configInfo.colorBlendInfo.blendConstants[0] = 0.0f;  // Optional
	configInfo.colorBlendInfo.blendConstants[1] = 0.0f;  // Optional
	configInfo.colorBlendInfo.blendConstants[2] = 0.0f;  // Optional
	configInfo.colorBlendInfo.blendConstants[3] = 0.0f;  // Optional

	configInfo.depthStencilInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO; // Set the type of the struct
	configInfo.depthStencilInfo.depthTestEnable = VK_TRUE; // Set the depth test enable
	configInfo.depthStencilInfo.depthWriteEnable = VK_TRUE; // Set the depth write enable
	configInfo.depthStencilInfo.depthCompareOp = VK_COMPARE_OP_LESS; // Set the depth compare op
	configInfo.depthStencilInfo.depthBoundsTestEnable = VK_FALSE; // Set the depth bounds test enable
	configInfo.depthStencilInfo.minDepthBounds = 0.0f;  // Optional
	configInfo.depthStencilInfo.maxDepthBounds = 1.0f;  // Optional
	configInfo.depthStencilInfo.stencilTestEnable = VK_FALSE; // Set the stencil test enable
	configInfo.depthStencilInfo.front = {};  // Optional
	configInfo.depthStencilInfo.back = {};   // Optional
    
    
    return configInfo; // Return the pipeline config info
}

std::vector<char> FL_Pipeline::readFile(const std::string& filePath)
{
    //std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl; // Debug statement
    //std::cout << "Attempting to open file:" << filePath << std::endl; // Debug statement

    std::ifstream file(filePath, std::ios::ate | std::ios::binary); // Open the file in binary mode and set the file pointer to the end of the file
    if (!file.is_open()) // Check if the file can be opened
    {
        throw std::runtime_error("Failed to open file: " + filePath);  // Throw an exception if the file cannot be opened
    }

    size_t fileSize = (size_t)file.tellg(); // Get the file size
    std::vector<char> buffer(fileSize); // Create a buffer of the file size

    file.seekg(0); // Move the file pointer to the beginning of the file
    file.read(buffer.data(), fileSize); // Read the file

    file.close(); // Close the file

    return buffer; // Return the buffer
}

void FL_Pipeline::createGraphicsPipeline(const std::string& vertFilePath, const std::string& fragFilePath, const PipelineConfigInfo& configInfo)
{
	assert(configInfo.pipelineLayout != VK_NULL_HANDLE && "Cannot create graphics pipeline:: no pipelineLayout provided in configInfo"); // Check if the pipeline config info is valid
	assert(configInfo.renderPass != VK_NULL_HANDLE && "Cannot create graphics pipeline:: no renderPass provided in configInfo"); // Check if the pipeline config info is valid
    auto vertCode = readFile(vertFilePath); // Read the vertex shader file
    auto fragCode = readFile(fragFilePath); // Read the fragment shader file

    logger.information("Vertex Shader Code Size: " + std::to_string(vertCode.size()));
    logger.information("Fragment Shader Code Size: " + std::to_string(fragCode.size()));

	createShaderModule(vertCode, &vertShaderModule); // Create the vertex shader module
	createShaderModule(fragCode, &fragShaderModule); // Create the fragment shader module

	VkPipelineShaderStageCreateInfo shaderStages[2]; // Create an array of shader stage create info structs
	shaderStages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO; // Set the type of the struct
	shaderStages[0].stage = VK_SHADER_STAGE_VERTEX_BIT; // Set the stage
	shaderStages[0].module = vertShaderModule; // Set the module
	shaderStages[0].pName = "main"; // Set the name
	shaderStages[0].flags = 0; // Set the flags
	shaderStages[0].pSpecializationInfo = nullptr; // Set the specialization info

	shaderStages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO; // Set the type of the struct
	shaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT; // Set the stage
	shaderStages[1].module = fragShaderModule; // Set the module
	shaderStages[1].pName = "main"; // Set the name
	shaderStages[1].flags = 0; // Set the flags
	shaderStages[1].pSpecializationInfo = nullptr; // Set the specialization info

	VkPipelineVertexInputStateCreateInfo vertexInputInfo = {}; // Create a vertex input state create info struct
	vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO; // Set the type of the struct
	vertexInputInfo.vertexAttributeDescriptionCount = 0; // Set the vertex attribute description count
	vertexInputInfo.vertexBindingDescriptionCount = 0; // Set the vertex binding description count
	vertexInputInfo.pVertexAttributeDescriptions = nullptr; // Set the vertex binding descriptions
	vertexInputInfo.pVertexBindingDescriptions = nullptr; // Set the vertex binding descriptions

	VkGraphicsPipelineCreateInfo pipelineInfo = {}; // Create a graphics pipeline create info struct
	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO; // Set the type of the struct
	pipelineInfo.stageCount = 2; // Set the stage count
	pipelineInfo.pStages = shaderStages; // Set the stages
	pipelineInfo.pVertexInputState = &vertexInputInfo; // Set the vertex input state
	pipelineInfo.pInputAssemblyState = &configInfo.inputAssemblyInfo; // Set the input assembly state
	pipelineInfo.pViewportState = &configInfo.viewportInfo; // Set the viewport state
	pipelineInfo.pRasterizationState = &configInfo.rasterizationInfo; // Set the rasterization state
	pipelineInfo.pMultisampleState = &configInfo.multisampleInfo; // Set the multisample state
	pipelineInfo.pColorBlendState = &configInfo.colorBlendInfo; // Set the color blend state
	pipelineInfo.pDepthStencilState = &configInfo.depthStencilInfo; // Set the depth stencil state
	pipelineInfo.pDynamicState = nullptr; // Set the dynamic state
	pipelineInfo.layout = configInfo.pipelineLayout; // Set the layout
	pipelineInfo.renderPass = configInfo.renderPass; // Set the render pass
	pipelineInfo.subpass = configInfo.subpass; // Set the subpass index
	pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // Set the base pipeline handle to null
	pipelineInfo.basePipelineIndex = -1; // Set the base pipeline index to -1

	if (vkCreateGraphicsPipelines(device.device(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS) // Create the graphics pipeline
	{
		logger.runtimeError("Failed to create graphics pipeline"); // Throw an exception if the graphics pipeline cannot be created
	}
}

void FL_Pipeline::createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule)
{
	VkShaderModuleCreateInfo createInfo = {}; // Create a shader module create info struct
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO; // Set the type of the struct
	createInfo.codeSize = code.size(); // Set the code size
	createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data()); // Set the code
	if (vkCreateShaderModule(device.device(), &createInfo, nullptr, shaderModule) != VK_SUCCESS) // Create the shader module
	{
		throw std::runtime_error("Failed to create shader module"); // Throw an exception if the shader module cannot be created
	}
}
