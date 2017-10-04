#include "rgengine_include.h"
#include "rgengine_application.h"

namespace rg::rgengine{
	RgEngineApplication::RgEngineApplication()
	{
	}
	RgEngineApplication::~RgEngineApplication()
	{
	}
	void RgEngineApplication::Run()
	{
		std::cout << "rigel engine" << std::endl;
		getchar();
	}
}