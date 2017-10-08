#pragma once
#include "rgcore.h"
#include "rg_windowManager.h"

#ifdef  _MSC_VER
#include "rg_windowWindows.h"
#endif //  _MSC_VER


namespace rg {
	HRESULT RgWindowManager::createWindow(RgWindow ** pwindow, RgWindowSettings * pwindowSettings)
	{
#ifdef _MSC_VER
		*pwindow = new RgWindowWindows();
		(*pwindow)->initWindow(pwindowSettings);
#else __GNUC__

#endif

		return S_OK;
	}
	void RgWindowManager::registerWindow(RgWindow * pwindow)
	{
		m_pWindow = pwindow;
		m_vWindows.push_back(pwindow);
		pwindow->onRegister();
	}
	void RgWindowManager::releaseWindow()
	{
		if (m_vWindows.capacity() == 0) return;
		for each (auto win in m_vWindows)
		{
			if (win != nullptr) {
				win->closeWindow();
				win->releaseWindow();
				delete win;
				win = nullptr;
			}
		}
		std::vector<RgWindow*>().swap(m_vWindows);
	}
	int RgWindowManager::enterMainLoop()
	{
		//MainLoop
		bool bgotMsg;
		MSG msg;
		msg.message = WM_NULL;
		PeekMessage(&msg, nullptr, 0U, 0U, PM_NOREMOVE);
		while (WM_QUIT != msg.message)
		{
			bgotMsg = (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE) != 0);
			if (bgotMsg) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			if (m_pWindow != nullptr) m_pWindow->onFrame();

			//Sleep(10);
		}

		return 0;
	}
	RgWindowManager::RgWindowManager()
	{
	}
	RgWindowManager::~RgWindowManager()
	{
		releaseWindow();
	}
}

