#include "rg_window.h"
#include "rg_windowManager.h"

#include <iostream>

#ifdef _MSC_VER
#include "rg_windowWindows.h"
#else __GNUC__

#endif


namespace rg {
	RgWindow::RgWindow()
	{

	}

	void RgWindow::onRegister()
	{
		if (m_funcREGISTER)m_funcREGISTER(this);
	}

	void RgWindow::onResize()
	{
	}

	void RgWindow::onPaint()
	{
	}

	void RgWindow::onEnterSizeMove()
	{
	}

	void RgWindow::onExitSizeMove()
	{
	}

	void RgWindow::onKeyboard()
	{
	}

	void RgWindow::onClose()
	{
		if(m_funcONCLOSE)
			m_funcONCLOSE(this);
	}

	void RgWindow::onDestroy()
	{
	}

	void RgWindow::onMouseButton()
	{
	}

	void RgWindow::onMouseWheel()
	{
	}

	void RgWindow::initWindow(RgWindowSettings * settings)
	{
	}

	RgWindow::~RgWindow()
	{

	}
}


