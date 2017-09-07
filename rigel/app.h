#pragma once
#include <rgcore\rgcore.h>
#include <Windows.h>

#include <rgcore\rg_windowManager.h>
#include <rgcore\rg_module_font.h>
#include <rggraphics\rg_graphicsAPI.h>

using namespace rg;

class RigelApp {

private:
	RgWindow *m_pWindow = nullptr;
	RgGraphicsContext * m_pGraphicsCtx = nullptr;

public:
	RigelApp();
	~RigelApp();
public:
	void Run();
	void onRegisterWindow();
	void onRender();

private:


};