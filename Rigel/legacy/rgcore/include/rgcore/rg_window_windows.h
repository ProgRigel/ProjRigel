#pragma once
#include "rg_window.h"

namespace rg {

	class RgWindowWindows : public RgWindow
	{
	public:
		RgWindowWindows();
		~RgWindowWindows();
		void* getHandler() const;
		LRESULT memberWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	protected:
		
		void Destroy();
	public:
		void InitWindow(RgWindowSettings* settings);
		void Show();
		void Close();



	private:
		RgWindowWindows(const RgWindowWindows&) = delete;
		RgWindowWindows& operator=(const RgWindowWindows&) = delete;
		

	private:
		HINSTANCE m_hInstance;
		HWND m_hWnd;

		LPCWSTR m_pWinClassName = nullptr;
	};

}