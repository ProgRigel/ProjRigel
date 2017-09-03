#include <Windows.h>
#include <iostream>

#include <rgcore\rg_pluginmanager.h>
#include <rgcore\rg_windowManager.h>
#include <rgcore\rg_module_font.h>
using namespace rg;

//Modules
RgModuleFont* g_pmoduleFont = new RgModuleFont();

int main() {

	RgPluginManager& pluginMgr = RgPluginManager::getInstance();
	pluginMgr.registerPlugin(g_pmoduleFont);


	RgWindowManager& windowMgr = RgWindowManager::getInstance();

	RgWindow* mainWin = nullptr;
	RgWindowCreateWindow(&mainWin, 0);
	windowMgr.registerWindow(mainWin);

	mainWin->ShowWindow();
	mainWin->CloseWindow();

	getchar();

	return 0;
}