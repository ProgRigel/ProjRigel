#include <rgcore\rgcore.h>
#include <Windows.h>

#include <rgcore\rg_module_font.h>

using namespace rg;

//Modules
RgModuleFont* g_pmoduleFont = new RgModuleFont();

void WindowOnRegister(RgWindow* win) {
	RgLogD() << "window register";

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
	RgWindowManager::createWindow(&mainWin, &settings);

	mainWin->regCallbackREGISTER(WindowOnRegister);
	mainWin->regCallbackONCLOSE(WindowOnClose);

	windowMgr.registerWindow(mainWin);

	

	mainWin->showWindow();

	windowMgr.enterMainLoop();

	return 0;
}