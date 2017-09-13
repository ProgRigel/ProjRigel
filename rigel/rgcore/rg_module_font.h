#pragma once
namespace rg {
	class RgPluginBase;
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