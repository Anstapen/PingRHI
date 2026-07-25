#pragma once
#include <cstdint>

namespace Mupfel
{
class Application;
class Renderer;

struct Animation
{
	friend class Application;
	friend class Renderer;
	uint32_t firstFrame = 0;
	uint32_t frameCount = 1;
	float	 fps = 10.0f;

private:
	float	 elapsed = 0.0f;
	uint32_t currentFrame = 0;
};
} // namespace Mupfel
