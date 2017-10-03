#pragma once
#include "rgcore.h"
#include "rg_window.h"

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
		EventOnFrame.emit();
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


