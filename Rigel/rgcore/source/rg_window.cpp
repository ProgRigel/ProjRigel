#pragma once
#include "rgcore.h"
#include "rg_window.h"

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

	RgWindow::~RgWindow()
	{

	}
}


