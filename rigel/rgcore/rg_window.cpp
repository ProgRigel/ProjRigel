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

	void RgWindow::regCallbackMsgProc(RGWINDOW_CALLBACK_MSGPROC func)
	{
		m_funcMsgProc = func;
	}

	void RgWindow::regCallbackNewFrame(RGWINDOW_CALLBACK_NEWFRAME func)
	{
		m_funcNewframe = func;
	}

	RgWindow::~RgWindow()
	{

	}
	HRESULT RgWindowCreateWindow(RgWindow ** pwindow, RgWindowSettings* windowSettings)
	{
#ifdef _MSC_VER
		*pwindow = new RgWindowWindows();
		(*pwindow)->InitWindow(windowSettings);
#else __GNUC__

#endif

		return S_OK;
	}
}


