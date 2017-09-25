#pragma once
namespace rg {
	class RgPluginBase
	{
	public:
		RgPluginBase();
		HINSTANCE m_hInstance;
		std::wstring m_wsName;
		virtual ~RgPluginBase() = default;
		virtual const char* GetPluginName() = 0;
		virtual void LoadPlugin() = 0;
		virtual void ReleasePlugin() = 0;
	private:
		RgPluginBase(const RgPluginBase&) = delete;
		const RgPluginBase& operator=(const RgPluginBase&) = delete;
	};
}