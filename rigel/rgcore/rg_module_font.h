#pragma once
#include "rg_pluginmanager.h"

namespace rg {
	class RgModuleFont :public RgPluginBase {

	public:
		RgModuleFont();
		~RgModuleFont();
	public:
		const char* GetPluginName();
		void LoadPlugin();
		void ReleasePlugin();
	};
}