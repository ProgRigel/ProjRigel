#include "rg_windowManager.h"

namespace rg {
	void RgWindowManager::registerWindow(RgWindow * pwindow)
	{
		m_vWindows.push_back(pwindow);
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

