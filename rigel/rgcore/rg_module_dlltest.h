#pragma once
#include "rg_pluginbase.h"
namespace rg
{
	typedef void(*DISP_ASTERISK)(int);
	class RgModuleDlltest :public RgPluginBase
	{
	public:
		RgModuleDlltest();
		~RgModuleDlltest();
	public:
		const char* GetPluginName();
		void LoadPlugin();
		void ReleasePlugin();
	public:
		DISP_ASTERISK m_disp_asterisk;
	};
}
