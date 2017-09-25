#include "rgcore.h"
#include "rg_module_dlltest.h"

namespace rg
{
	RgModuleDlltest::RgModuleDlltest()
	{
		m_wsName = L"..\\Debug\\rgdlltest.dll";
		std::wcout << m_wsName << std::endl;
		std::cout << "ctor dlltest" << std::endl;
	}


	RgModuleDlltest::~RgModuleDlltest()
	{
		std::cout << "dtor dlltest" << std::endl;
	}
	const char * RgModuleDlltest::GetPluginName()
	{
		return nullptr;
	}
	void RgModuleDlltest::LoadPlugin()
	{
		std::cout << "loading" << std::endl;
		if (m_hInstance != NULL)
		{
			m_disp_asterisk = (DISP_ASTERISK)GetProcAddress(m_hInstance,"disp_asterisk");
		}
		if (m_disp_asterisk != NULL)
		{
			std::cout << "load dlltest" << std::endl;
		}
	}
	void RgModuleDlltest::ReleasePlugin()
	{
		std::cout << "release dlltest" << std::endl;
	}
}