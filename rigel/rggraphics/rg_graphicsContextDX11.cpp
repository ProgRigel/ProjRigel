#include "rg_graphicsContextDX11.h"
#include <iostream>

namespace rg {
	RgGraphicsContextDX11::RgGraphicsContextDX11()
	{
		
	}
	RgGraphicsContextDX11::~RgGraphicsContextDX11()
	{
	}
	void RgGraphicsContextDX11::init()
	{
		std::cout << "init dx11 api" << std::endl;
	}
	void RgGraphicsContextDX11::release()
	{
		std::cout << "release dx11 api" << std::endl;
	}
}

