#include "stdafx.h"
#include "app_graphics.h"
#include <rggraphics\rg_render_context.h>
#include <rggraphics\rg_graphicsAPI.h>
#include <rggraphics\rg_graphicscontext.h>
#include <rggraphics\rg_inputlayout.h>
#include <rggui\rg_gui.h>
#include <rggui\rg_gui_draw_buffer.h>
#include <rggui\rg_gui_context.h>

using namespace rg;

namespace editor {

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
		settings.OutputWindow = (HWND)window->getHandler();
		settings.Windowed = true;

		m_pRgGraphicsCtx = RgGraphicsAPI::InitAPI(RG_GRAPHICS_API::RG_GRAPHICS_APY_DX11, &settings);

		//register callback
		window->EventOnResize.connect<RigelAppGraphics, &RigelAppGraphics::OnEventResize>(this);
		window->EventOnExitSizeMove.connect<RigelAppGraphics, &RigelAppGraphics::onEventExitResize>(this);

	}

	void RigelAppGraphics::Render()
	{
	}

	void RigelAppGraphics::SetFullScreen(bool fullscreen) const
	{
		m_pRgGraphicsCtx->SetFullScreen(fullscreen);
	}

	void RigelAppGraphics::OnEventResize(unsigned int width, unsigned int height)
	{
		m_bNeedResize = true;
		m_uResizeWidth = width;
		m_uResizeHeight = height;

		m_pRgGraphicsCtx->resizeBuffer(m_uResizeWidth, m_uResizeHeight);
	}

	void RigelAppGraphics::onEventExitResize()
	{
	}


}

