#include <rgcore\rgcore.h>
#include <Windows.h>

#include <rgcore\rg_module_font.h>

using namespace rg;

//Modules
RgModuleFont* g_pmoduleFont = new RgModuleFont();

void WindowOnCreate(RgWindow* win) {


}

void WindowOnClose(RgWindow* win) {
	RgLogD() << "window close";
}

int main() {

	RgPluginManager& pluginMgr = RgPluginManager::getInstance();
	pluginMgr.registerPlugin(g_pmoduleFont);


	RgWindowManager& windowMgr = RgWindowManager::getInstance();

	RgWindow* mainWin = nullptr;
	RgWindowSettings settings;
	RgWindowCreateWindow(&mainWin, &settings);
	windowMgr.registerWindow(mainWin);

	mainWin->regCallbackONCREATE(WindowOnCreate);
	mainWin->regCallbackONCLOSE(WindowOnClose);

	mainWin->showWindow();

	windowMgr.enterMainLoop();

	return 0;
}