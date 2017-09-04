#include <rgcore\rgcore.h>
#include <Windows.h>

#include <rgcore\rg_module_font.h>
#include <rggraphics\rg_graphicsAPI.h>

using namespace rg;

//Modules
RgModuleFont* g_pmoduleFont = new RgModuleFont();

RgGraphicsContext * graphicsCtx = nullptr;

void WindowOnRegister(RgWindow* win) {
	RgLogD() << "window register";

	RG_GRAPHICS_INIT_SETTINGS settings;
	settings.Windowed = true;
	settings.OutputWindow = (HWND)win->getHandler();
	settings.BufferWidth = win->getWidth();
	settings.BufferHeight = win->getHeight();


	graphicsCtx = RgGraphicsAPI::InitAPI(RG_GRAPHICS_APY_DX11,&settings);

}

void WindowOnResize(RgWindow* win, UINT width, UINT height) {

}

void WindowOnExitSizeMove(RgWindow* win) {
	
	
	
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

	mainWin->regCallback_REGISTER(WindowOnRegister);
	mainWin->regCallback_ONCLOSE(WindowOnClose);
	mainWin->regCallback_ONRESIZE(WindowOnResize);
	mainWin->regCallback_EXIT_RESIZE_MOVE(WindowOnExitSizeMove);

	windowMgr.registerWindow(mainWin);

	

	mainWin->showWindow();

	windowMgr.enterMainLoop();

	return 0;
}