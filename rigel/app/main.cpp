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

void WindowOnFrame(RgWindow* win) {
	if(graphicsCtx != nullptr)
		graphicsCtx->render();
}

void WindowOnExitSizeMove(RgWindow* win) {
	
	if (win->getIsResized()) {
		graphicsCtx->resizeBuffer(win->getWidth(), win->getHeight());
	}
	
}

void WindowOnClose(RgWindow* win) {
	RgLogD() << "window close";


	RgGraphicsAPI::ReleaseAPI(graphicsCtx);
	graphicsCtx = 0;
}

void tt() {

}

int main() {

	Signal<void()> t;
	t.connect<tt>();
	t.emit();

	RgPluginManager& pluginMgr = RgPluginManager::getInstance();
	pluginMgr.registerPlugin(g_pmoduleFont);


	RgWindowManager& windowMgr = RgWindowManager::getInstance();

	RgWindow* mainWin = nullptr;
	RgWindowSettings settings;
	RgWindowManager::createWindow(&mainWin, &settings);


	//mainWin->regCallback_REGISTER(WindowOnRegister);
	//mainWin->regCallback_ONCLOSE(WindowOnClose);
	//mainWin->regCallback_ONRESIZE(WindowOnResize);
	//mainWin->regCallback_EXIT_RESIZE_MOVE(WindowOnExitSizeMove);
	//mainWin->regCallback_ON_FRAME(WindowOnFrame);
	windowMgr.registerWindow(mainWin);

	

	mainWin->showWindow();

	windowMgr.enterMainLoop();

	return 0;
}

