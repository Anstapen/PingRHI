#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include <chrono>

#include "Ping/Ping.h"
#include "Ping/Device.h"
#include "Renderer/Renderer.h"
#include "Window.h"

int main()
{
	std::cout << "Hello Triangle!" << std::endl;

	/* Initialize the RHI. */
	if (!Ping::Init())
	{
		std::cout << "Unable to initialize RHI! Exiting..." << std::endl;
	}

	/* Create a window to draw things on. */
	Window window;

	/* Create a GPU device. */
	Ping::Device device(Ping::DeviceSpecification(), window.GetGLFWHandle());

	/** Owns the swapchain/pipeline/command buffers for rendering. */
	Renderer	 renderer;

	renderer.Init(device, window);

	auto lastFrameTime = std::chrono::steady_clock::now();

	while (!window.shouldClose())
	{
		window.pollEvents();

		auto  now = std::chrono::steady_clock::now();
		float delta_time = std::chrono::duration<float>(now - lastFrameTime).count();
		lastFrameTime = now;

		renderer.RenderNextFrame(device, window, delta_time);
	}


	/* DeInit the RHI */
	device.WaitForCommands();

	/* TODO: there may be GLFW services called after glfwTerminate has been called... */
	Ping::Shutdown();

	return EXIT_SUCCESS;
}