#pragma once
#include "rg_inc.h"
#include "rg_window.h"
#include <vector>
namespace rg {

	class RgWindowManager
	{
	public:
		static RgWindowManager& getInstance() {
			static RgWindowManager instance;
			return instance;
		}
	public:
		static HRESULT createWindow(RgWindow** pwindow, RgWindowSettings* pwindowSettings);
		void registerWindow(RgWindow* pwindow);
		void releaseWindow();

		int enterMainLoop();

	private:
		RgWindowManager();
		~RgWindowManager();
		RgWindowManager(const RgWindowManager&) = delete;
		RgWindowManager& operator=(const RgWindowManager&) = delete;

	private:
		std::vector<RgWindow*> m_vWindows;

		RgWindow * m_pWindow = nullptr;
	};
}