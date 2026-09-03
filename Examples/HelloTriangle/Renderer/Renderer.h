#pragma once

#include <cstdint>
#include <filesystem>
#include <optional>
#include <string>

#include "Ping/Buffer.h"
#include "Ping/DescriptorSets.h"
#include "Ping/Device.h"
#include "Ping/Gui.h"
#include "Ping/Image.h"
#include "Ping/Sampler.h"

#include "Window.h"


/**
 * Drives per-frame rendering on top of the `Ping` RHI: owns the swapchain, pipeline, command
 * buffers, and one vertex buffer per frame in flight, and syncs `Transform` components from the
 * `World` into those buffers each frame.
 */
class Renderer
{
public:
	/** Creates the swapchain, pipeline, command buffers, and per-frame-in-flight vertex buffers for `window`. */
	void Init(const Ping::Device& device, const Window& window);

	void RenderNextFrame(const Ping::Device& device, const Window& window, float delta_time);

	void Shutdown();

	void SetImageBuffer(const Ping::Device& device, std::vector<Ping::Image>& image_buffer);

private:
	/** Advances `frameIndex` to the next frame-in-flight slot, wrapping at `frames_in_flight`. */
	void incrementFrameIndex();

private:
	/** Number of frames pipelined in parallel. */
	static constexpr uint32_t frames_in_flight = 2;
	/** Current frame-in-flight slot, in `[0, frames_in_flight)`. */
	uint32_t frameIndex = 0;
	/** Empty until `Init` runs. */
	std::optional<Ping::SwapChain> swapchain;
	/** Empty until `Init` runs. */
	std::optional<Ping::Pipeline> pipeline;
	/** One per frame in flight; empty until `Init` runs. */
	std::optional<Ping::CommandBuffers> commandBuffers;
	/** One host-visible vertex buffer per frame in flight. */
	std::vector<Ping::Buffer> vertex_buffers;
	/** One device-local index buffer */
	std::optional<Ping::Buffer> index_buffer;
};
