#include "rgengine_graphics.h"
#include "rgengine_window.h"
namespace rg::rgengine {

	RgEngineGraphics* RgEngineGraphics::m_pInstance = nullptr;

	RgEngineGraphics * RgEngineGraphics::GetInstance()
	{
		if (m_pInstance == nullptr) {
			m_pInstance = new RgEngineGraphics();
		}
		return m_pInstance;
	}

	RgEngineGraphics * RgEngineGraphics::Release(RgEngineGraphics * graphics)
	{
		if (graphics != nullptr) {
			delete graphics;
			graphics = nullptr;
		}
		return graphics;
	}

	bool RgEngineGraphics::Init(const RgEngineExternalAdapter & adapter)
	{
		auto rgwindow = RgEngineWindow::GetInstance()->InternalGetWindow();
		

		RG_GRAPHICS_INIT_SETTINGS settings;
		settings.BufferWidth = rgwindow->getWidth();
		settings.BufferHeight = rgwindow->getHeight();
		settings.OutputWindow = (HWND)rgwindow->getHandler();
		settings.Windowed = true;

		m_pRgGraphicsContext = RgGraphicsAPI::InitAPI(RG_GRAPHICS_API::RG_GRAPHICS_APY_DX11, &settings);

		rgwindow->EventOnResize.connect<RgEngineGraphics, &RgEngineGraphics::InternalProcessWindowResize>(this);
		rgwindow->EventOnExitSizeMove.connect<RgEngineGraphics, &RgEngineGraphics::InternalProcessWindowExitResize>(this);
		rgwindow->EventOnEnterSizeMove.connect<RgEngineGraphics, &RgEngineGraphics::InternalProcessWindowEnterResize>(this);

		return true;
	}



	RgEngineGraphics::RgEngineGraphics()
	{
	}

	RgEngineGraphics::~RgEngineGraphics()
	{
		Release();
		m_pInstance = nullptr;

		RgLogW() << "release RgEngineGraphics";
	}

	void RgEngineGraphics::Release()
	{
		RgGraphicsAPI::ReleaseAPI(m_pRgGraphicsContext);
		m_pRgGraphicsContext = nullptr;
	}

	void RgEngineGraphics::InternalProcessWindowResize(unsigned int width, unsigned int height)
	{
		if (m_bOnWindowDrag == false) m_pRgGraphicsContext->resizeBuffer(0, 0);
	}

	void RgEngineGraphics::InternalProcessWindowExitResize()
	{
		if (m_bOnWindowDrag) {
			m_pRgGraphicsContext->resizeBuffer(0, 0);
			m_bOnWindowDrag = false;
		}
	}

	void RgEngineGraphics::InternalProcessWindowEnterResize()
	{
		m_bOnWindowDrag = true;
	}


}
