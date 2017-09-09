#pragma once
#include <rgcore\rgcore.h>
#include <Windows.h>

#include <rgcore\rg_windowManager.h>
#include <rgcore\rg_module_font.h>
#include <rggraphics\rg_graphicsAPI.h>

#include "app_graphics.h"

using namespace rg;

class RigelApp {

private:
	RgWindow *m_pWindow = nullptr;
	RigelAppGraphics * m_pAppGraphics = nullptr;
public:
	RigelApp();
	~RigelApp();
public:
	void Run();
	void onRegisterWindow();
	void onRender();

private:


};