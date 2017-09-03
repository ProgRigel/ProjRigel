#include <Windows.h>
#include <iostream>

#include <rgcore\rg_pluginmanager.h>
#include <rgcore\rg_module_font.h>
using namespace rg;

RgModuleFont* g_pmoduleFont = new RgModuleFont();

int main() {
	

	RgPluginManager& pluginMgr = RgPluginManager::getInstance();

	pluginMgr.registerPlugin(g_pmoduleFont);

	getchar();



	pluginMgr.releasePlugins();
	return 0;
}