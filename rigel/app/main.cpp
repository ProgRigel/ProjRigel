#include <rgcore\rgcore.h>
#include <Windows.h>

#include <rgcore\rg_module_font.h>
#include <rggraphics\rg_graphicsAPI.h>

using namespace rg;

//Modules
RgModuleFont* g_pmoduleFont = new RgModuleFont();

RgGraphicsContext * graphicsCtx;

void WindowOnRegister(RgWindow* win) {
	RgLogD() << "window register";

	graphicsCtx = RgGraphicsAPI::InitAPI(RG_GRAPHICS_APY_DX11);

}

void WindowOnClose(RgWindow* win) {
	RgLogD() << "window close";


	RgGraphicsAPI::ReleaseAPI(graphicsCtx);
	graphicsCtx = 0;
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