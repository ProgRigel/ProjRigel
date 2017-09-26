#include <Windows.h>
#include <rgcore\rgcore.h>
#include <rggraphics\rg_graphicsAPI.h>
#include <rggui\rg_gui.h>
#include <rgcore\rg_utility.h>
#include <rgcore\rg_pluginmanager.h>
#include <rgcore\rg_module_dlltest.h>
using namespace rg;

#define Check(h,l) if((h) == false) RgLogW()<<l;

int main() {

	RgLogD() << "Start Unitest";
	RgLogD() << "=================";
	//rg_math.h
	{
		RgVec2 v(10, -20);
		v = v + v;
		Check(v.x == 20 && v.y == -41, "RgVec2 + fail");
	}
	//rg_utility.h
	HRESULT hr;
	hr = S_FALSE;
	std::wcout <<"test:HrToMessage:"<< HrToMessage(hr) << std::endl;;
	//rg_dlltest
	RgModuleDlltest dlltest;
	RgPluginManager* PluginManager = RgPluginManager::getInstance();
	PluginManager->registerPlugin((RgPluginBase*)&dlltest);
	dlltest.m_disp_asterisk(10);
	
	RgLogD() << "=================";
	RgLogD() << "Unitest Done!";
	getchar();
	return 0;
}

