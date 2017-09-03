#pragma once
#include "rg_window.h"

namespace rg {

	class RgWindow;

	class RgWindowWindows : public RgWindow
	{
	public:
		RgWindowWindows();
		
	protected:
		
		void releaseWindow();
	public:
		void initWindow(RgWindowSettings* settings);
		void showWindow();
		void closeWindow();



	private:
		RgWindowWindows(const RgWindowWindows&) = delete;
		RgWindowWindows& operator=(const RgWindowWindows&) = delete;

	private:
		HINSTANCE m_hInstance;
		HWND m_hWnd;
	};

}