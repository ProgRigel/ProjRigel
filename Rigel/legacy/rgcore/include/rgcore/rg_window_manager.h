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
		static HRESULT CreateWindowWithSettings(RgWindow** pwindow, RgWindowSettings* pwindowSettings);
		static void ReleaseWindow();
		static void ReleaseChildWindow(RgWindow * pchildWindow);
		static void CreateChildWindow();
		static RgWindow * FindWindowByHandler(void * handle);

		static int EnterRunLoop(unsigned int millisecond = 0);
		static bool CheckExitRunLoop();

		static RgWindow * GetCurrentActiveWindow();
		static RgWindow* GetMainWindow();
		
		static void InternalRegisterWindow(RgWindow * winptr);

	private:
		RgWindowManager();
		~RgWindowManager();
		RgWindowManager(const RgWindowManager&) = delete;
		RgWindowManager& operator=(const RgWindowManager&) = delete;

	private:
		static std::vector<RgWindow*> m_vChildWindows;
		static RgWindow * m_pMainWindow;
	};
}