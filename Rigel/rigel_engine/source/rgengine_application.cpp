#include "rgengine_include.h"
#include "rgengine_application.h"
#include "rgengine_external_adapter.h"

namespace rg::rgengine{
	RgEngineApplication::RgEngineApplication()
	{
	}
	RgEngineApplication::~RgEngineApplication()
	{
	}
	void RgEngineApplication::Run(const RgEngineExternalAdapter & adapter)
	{
		std::cout << "rigel engine" << std::endl;
		getchar();
	}

}