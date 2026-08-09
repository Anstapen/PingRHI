#include "Application/Application.h"
#include <cstdlib>
#include <stdexcept>

using namespace Mupfel;

int main()
{

	try
	{
		Application app("Vulkan Playground");
		app.Run();
	}
	catch (const std::exception& e)
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}