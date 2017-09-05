#include "rg_window.h"
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
		if (m_func_REGISTER)m_func_REGISTER(this);
	}

	void RgWindow::onResize(unsigned int width, unsigned int height)
	{
		m_width = width;
		m_height = height;
		m_resized = true;
		if (m_func_ONRESIZE)m_func_ONRESIZE(this,width,height);
	}

	void RgWindow::onPaint()
	{
	}

	void RgWindow::onEnterSizeMove()
	{
		if (m_func_ENTER_RESIZE_MOVE) m_func_ENTER_RESIZE_MOVE(this);
	}

	void RgWindow::onExitSizeMove()
	{
		if (m_func_EXIT_RESIZE_MOVE)m_func_EXIT_RESIZE_MOVE(this);
		m_resized = false;
	}

	void RgWindow::onKeyboard()
	{
	}

	void RgWindow::onClose()
	{
		if(m_func_ONCLOSE)
			m_func_ONCLOSE(this);
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


