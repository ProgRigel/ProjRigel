#include "rggui.h"
#include "rg_gui_bind_graphics.h"
#include "rg_gui_context.h"

namespace rg {

	RgGUIBindGraphics::RgGUIBindGraphics(RgGUIContext * gui, RgGraphicsContext * graphics)
	{
		m_pGUICtx = gui;
		m_pGraphics = graphics;
	}
	RgGUIBindGraphics::~RgGUIBindGraphics()
	{
		Release();
	}
	void RgGUIBindGraphics::Release()
	{
		m_pGUICtx = nullptr;
		m_pGraphics = nullptr;
	}
}


