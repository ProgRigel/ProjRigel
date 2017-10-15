#pragma once
#include "rgcore.h"
#include "rg_window_manager.h"


namespace rg {

	std::vector<RgWindow*> RgWindowManager::m_vChildWindows;
	RgWindow * RgWindowManager::m_pMainWindow = nullptr;

	HRESULT RgWindowManager::CreateWindowWithSettings(RgWindow ** pwindow, RgWindowSettings * pwindowSettings)
	{
		if (m_pMainWindow != nullptr) {
			RgLogE() << "main window already created";
			return S_FALSE;
		}

#ifdef _MSC_VER
		(*pwindow) = new RgWindowWindows();
		(*pwindow)->InitWindow(pwindowSettings);
#else __GNUC__

#endif
		return S_OK;
	}
	void RgWindowManager::ReleaseWindow()
	{
		if (m_pMainWindow == nullptr) return;
		m_pMainWindow->Destroy();

		if (m_pMainWindow->m_destroyed) {
			delete m_pMainWindow;
			m_pMainWindow = nullptr;
		}
	}
	void RgWindowManager::ReleaseChildWindow(RgWindow * pchildWindow)
	{
		for (auto iter = m_vChildWindows.begin(); iter != m_vChildWindows.end(); iter++) {
			if (*iter == nullptr) {
				m_vChildWindows.erase(iter);
			}
			
		}
	}
	void RgWindowManager::CreateChildWindow()
	{
	}

	RgWindow * RgWindowManager::FindWindowByHandler(void * handle)
	{
		if (handle == nullptr) {
			RgLogE() << "handle is null";
			return nullptr;
		}

		if (m_pMainWindow != nullptr) {
			if (handle == m_pMainWindow->getHandler()) return m_pMainWindow;
		}
		else
		{
			RgLogD() << "main window null";
		}
			
		for each (RgWindow* winptr in m_vChildWindows)
		{
			if (winptr->getHandler() == handle) {
				return winptr;
			}
		}
		return nullptr;
	}

	int RgWindowManager::EnterRunLoop(unsigned int millisecond)
	{
		bool bgotMsg;
		MSG msg;
		msg.message = WM_NULL;
		PeekMessage(&msg, NULL, 0U, 0U, PM_NOREMOVE);
		while (WM_QUIT != msg.message)
		{

			bgotMsg = (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE) != 0);
			if (bgotMsg) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			auto mainwindow = RgWindowManager::GetMainWindow();
			if (RgWindowManager::CheckExitRunLoop()) {

				RgLogD() << RgLogStyle::Green << "exit window runloop";
				break;
			}
			else {
				if (msg.hwnd != nullptr) {
					auto window = RgWindowManager::FindWindowByHandler(msg.hwnd);
					if (window != nullptr) {
						window->onFrame();
					}
				}
			}


			if (msg.hwnd != nullptr) {
				auto window = RgWindowManager::FindWindowByHandler(msg.hwnd);
				if (window != nullptr) {
					window->onFrame();
				}
			}

			if(millisecond != 0)
				Sleep(millisecond);
		}

		return 0;
	}

	bool RgWindowManager::CheckExitRunLoop()
	{
		if (m_pMainWindow == nullptr) return true;
		if (m_pMainWindow->m_destroyed) {
			delete m_pMainWindow;
			m_pMainWindow = nullptr;
			return true;
		}
		return false;
	}

	RgWindow * RgWindowManager::GetCurrentActiveWindow()
	{
#ifdef _MSC_VER
		HWND hwnd = GetActiveWindow();
		if (hwnd == nullptr) return nullptr;
		for each (RgWindow* winptr in m_vChildWindows)
		{
			if (winptr->getHandler() == hwnd) {
				return winptr;
			}
		}
#elif __GNUC__

#else
		
#endif
		return nullptr;
	}
	RgWindow * RgWindowManager::GetMainWindow()
	{
		return m_pMainWindow;
	}
	void RgWindowManager::InternalRegisterWindow(RgWindow * winptr)
	{
		RG_ASSERT(winptr);
		if (winptr->m_bIsChild) {
			m_vChildWindows.push_back(winptr);
		}
		else
		{
			RgLogD() << "register main window";
			m_pMainWindow = winptr;
		}
	}
	RgWindowManager::RgWindowManager()
	{
	}
	RgWindowManager::~RgWindowManager()
	{

	}
}

