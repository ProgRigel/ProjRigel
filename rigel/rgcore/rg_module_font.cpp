#pragma once
#include "rgcore.h"
#include "rg_pluginbase.h"
#include "rg_module_font.h"

namespace rg {
	RgModuleFont::RgModuleFont()
	{
		std::cout << "ctor font" << std::endl;
	}
	RgModuleFont::~RgModuleFont()
	{
		std::cout << "dctor font" << std::endl;
	}
	const char * RgModuleFont::GetPluginName()
	{
		return nullptr;
	}
	void RgModuleFont::LoadPlugin()
	{
		std::cout << "load font" << std::endl;
	}
	void RgModuleFont::ReleasePlugin()
	{
		std::cout << "release font" << std::endl;
	}
}

