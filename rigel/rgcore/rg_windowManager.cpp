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
				win->CloseWindow();
				win->ReleaseWindow();
				delete win;
			}
		}
		std::vector<RgWindow*>().swap(m_vWindows);
	}
	RgWindowManager::RgWindowManager()
	{
	}
	RgWindowManager::~RgWindowManager()
	{
		releaseWindow();
	}
}

