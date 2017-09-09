#include "app_graphics.h"

using namespace rg;

RigelAppGraphics::RigelAppGraphics()
{
}

RigelAppGraphics::~RigelAppGraphics()
{
	Release();
}

void RigelAppGraphics::Release()
{
	RgGraphicsAPI::ReleaseAPI(m_pRgGraphicsCtx);
	m_pRgGraphicsCtx = nullptr;
}

void RigelAppGraphics::Init(RgWindow * window)
{
	RG_GRAPHICS_INIT_SETTINGS settings;
	settings.BufferHeight = window->getHeight();
	settings.BufferWidth = window->getWidth();
	settings.OutputWindow =(HWND) window->getHandler();
	settings.Windowed = true;

	m_pRgGraphicsCtx = RgGraphicsAPI::InitAPI(RG_GRAPHICS_API::RG_GRAPHICS_APY_DX11, &settings);

	//init draws
}

void RigelAppGraphics::Render()
{
	m_pRgGraphicsCtx->render();
}
