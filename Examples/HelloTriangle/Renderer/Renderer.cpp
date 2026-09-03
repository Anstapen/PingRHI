#include "Renderer.h"
#include "glm.hpp"

struct Vertex
{
	/** 2D position, bound to vertex shader location 0. */
	glm::vec2 pos;
	/** RGB color, bound to vertex shader location 1. */
	glm::vec3 color;

	static Ping::VertexBinding GetVertexLayout()
	{
		return {
			.binding = 0,
			.stride = sizeof(Vertex),
			.inputRate = Ping::VertexInputRate::Vertex,
			.attributes = {
				{0, Ping::VertexFormat::Float32x2, offsetof(Vertex, pos)},
				{1, Ping::VertexFormat::Float32x3, offsetof(Vertex, color)}}};
	}
};

static const std::vector<Vertex> vertices = {
	{{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
	{{0.0f, -0.5f}, {1.0f, 1.0f, 1.0f}},
	{{0.5f, 0.5f}, {1.0f, 0.0f, 1.0f}}};

static const std::vector<uint16_t> indices = {0, 2, 1};

void Renderer::Init(const Ping::Device& device, const Window& window)
{
	swapchain = device.CreateSwapChain(window.GetGLFWHandle(), frames_in_flight);
	Ping::PipelineSpecification pipeline_spec{
		"Shaders/slang.spv",
		Vertex::GetVertexLayout(),
		{},
		Ping::CullMode::Back,
		Ping::BlendFactor::Zero,
		false,
		swapchain.value().GetFormat()};
	pipeline = device.CreatePipeline(pipeline_spec);
	commandBuffers = device.CreateCommandBuffers(Ping::QueueType::Graphics, frames_in_flight);
	assert(commandBuffers.has_value() && commandBuffers.value().size() > 0);

	/* We need one vertex buffer for each frame in flight */
	for (uint32_t i = 0; i < frames_in_flight; i++)
	{
		/* Create vertex buffers. These hold the 3 vertices used to draw the triangle. */
		auto& buffer = vertex_buffers.emplace_back(device.CreateBuffer(
			sizeof(Vertex) * vertices.size(), Ping::BufferUsage::VertexBuffer,
			Ping::MemoryProperty::HostVisible | Ping::MemoryProperty::HostCoherent |
				Ping::MemoryProperty::DeviceLocal));
		auto* mapped_ptr = static_cast<Vertex*>(buffer.GetMappedPtr());

		/* Copy vertices */
		std::memcpy(mapped_ptr, vertices.data(), buffer.Size());
	}

	index_buffer = std::move(device.CreateBuffer(
		sizeof(uint16_t) * indices.size(), Ping::BufferUsage::IndexBuffer | Ping::BufferUsage::TransferDst,
		Ping::MemoryProperty::DeviceLocal));

	/* Copy indices */
	index_buffer.value().CopyHostData(device, indices.data(), sizeof(uint16_t) * indices.size());
}

void Renderer::RenderNextFrame(const Ping::Device& device, const Window& window, float delta_time)
{
	Ping::CommandBuffer& current_command_buffer = commandBuffers.value()[frameIndex];

	current_command_buffer.WaitForFences(device);

	uint32_t image_index = swapchain.value().AcquireNextImage(frameIndex);

	/* Check if the index is valid */
	if (image_index == std::numeric_limits<uint32_t>::max())
	{
		/* Image was resized, swapchain needs to be recreated */
		swapchain.value().Recreate(device, window.GetGLFWHandle(), frames_in_flight);
		return;
	}

	current_command_buffer.Begin(device, Ping::CommandBufferUsage::None);

	Ping::ImageLayoutTransition layout_transition = {
		.oldLayout = Ping::ImageLayout::Undefined,
		.newLayout = Ping::ImageLayout::ColorAttachmentOptimal,
		.srcAccessMask = Ping::AccessMask::None,
		.dstAccessMask = Ping::AccessMask::ColorAttachmentWrite,
		.srcStage = Ping::PipelineStage::ColorAttachmentOutput,
		.dstStage = Ping::PipelineStage::ColorAttachmentOutput,
		.aspect = Ping::ImageAspect::Color};

	current_command_buffer.transitionImageLayout(swapchain.value(), image_index, layout_transition);

	layout_transition.oldLayout = Ping::ImageLayout::Undefined;
	layout_transition.newLayout = Ping::ImageLayout::DepthAttachmentOptimal;
	layout_transition.srcAccessMask = Ping::AccessMask::DepthStencilAttachmentWrite;
	layout_transition.dstAccessMask = Ping::AccessMask::DepthStencilAttachmentWrite;
	layout_transition.srcStage = Ping::PipelineStage::EarlyFragmentTests | Ping::PipelineStage::LateFragmentTests;
	layout_transition.dstStage = Ping::PipelineStage::EarlyFragmentTests | Ping::PipelineStage::LateFragmentTests;
	layout_transition.aspect = Ping::ImageAspect::Depth;

	current_command_buffer.BeginRendering(swapchain.value(), image_index);

	current_command_buffer.BindPipeline(pipeline.value());

	current_command_buffer.BindVertexBuffer(vertex_buffers[frameIndex], 0);

	current_command_buffer.BindIndexBuffer(index_buffer.value());

	current_command_buffer.DrawIndexed(3, 1);

	current_command_buffer.EndRendering();

	layout_transition.oldLayout = Ping::ImageLayout::ColorAttachmentOptimal;
	layout_transition.newLayout = Ping::ImageLayout::PresentSource;
	layout_transition.srcAccessMask = Ping::AccessMask::ColorAttachmentWrite;
	layout_transition.dstAccessMask = Ping::AccessMask::None;
	layout_transition.srcStage = Ping::PipelineStage::ColorAttachmentOutput;
	layout_transition.dstStage = Ping::PipelineStage::BottomOfPipe;
	layout_transition.aspect = Ping::ImageAspect::Color;

	current_command_buffer.transitionImageLayout(swapchain.value(), image_index, layout_transition);

	current_command_buffer.End();

	current_command_buffer.Submit(device, swapchain.value(), frameIndex, image_index);

	if (!swapchain.value().Present(device, image_index))
	{
		/* Image was resized, swapchain needs to be recreated */
		swapchain.value().Recreate(device, window.GetGLFWHandle(), frames_in_flight);
	}

	incrementFrameIndex();
}

void Renderer::Shutdown() {}

void Renderer::incrementFrameIndex() { frameIndex = (frameIndex + 1) % frames_in_flight; }
