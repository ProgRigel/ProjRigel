#pragma once
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
		void registerWindow(RgWindow* pwindow);
		void releaseWindow();

	private:
		RgWindowManager();
		~RgWindowManager();
		RgWindowManager(const RgWindowManager&) = delete;
		RgWindowManager& operator=(const RgWindowManager&) = delete;

	private:
		std::vector<RgWindow*> m_vWindows;
	};
}