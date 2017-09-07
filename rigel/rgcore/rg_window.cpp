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

	void RgWindow::onFrame()
	{
	}

	void RgWindow::onRegister()
	{
		EventOnRegister.emit();
	}

	void RgWindow::initWindow(RgWindowSettings * settings)
	{

	}

	RgWindow::~RgWindow()
	{

	}
}


