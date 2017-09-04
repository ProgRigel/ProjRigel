#include "rg_windowWindows.h"
#include "rg_log.h"
#include <iostream>
namespace rg {

	RgWindow *g_winwindow;

	LRESULT CALLBACK RgWindowWindowsWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

		if (uMsg == WM_KEYDOWN || uMsg == WM_KEYUP || uMsg == WM_SYSKEYDOWN || uMsg == WM_SYSKEYUP) {
			g_winwindow->onKeyboard();
		}
		else if (uMsg == WM_LBUTTONDOWN ||
			uMsg == WM_LBUTTONUP ||
			uMsg == WM_LBUTTONDBLCLK ||
			uMsg == WM_MBUTTONDOWN ||
			uMsg == WM_MBUTTONUP ||
			uMsg == WM_MBUTTONDBLCLK ||
			uMsg == WM_RBUTTONDOWN ||
			uMsg == WM_RBUTTONUP ||
			uMsg == WM_RBUTTONDBLCLK ||
			uMsg == WM_XBUTTONDOWN ||
			uMsg == WM_XBUTTONUP ||
			uMsg == WM_XBUTTONDBLCLK)
		{
			g_winwindow->onMouseButton();
		}
		else if (uMsg == WM_MOUSEWHEEL)
		{
			g_winwindow->onMouseWheel();
		}
		else if (uMsg == WM_MOUSEMOVE) {

		}

		switch (uMsg) {
		case WM_PAINT:
			g_winwindow->onPaint();
			break;
		case WM_SIZE:
			g_winwindow->onResize((UINT)LOWORD(lParam),(UINT)HIWORD(lParam));
			break;
		case WM_ENTERSIZEMOVE:
			g_winwindow->onEnterSizeMove();
			break;
		case WM_EXITSIZEMOVE:
			g_winwindow->onExitSizeMove();
			break;
		case WM_CLOSE:
			g_winwindow->onClose();
			break;
		case WM_DESTROY:
			g_winwindow->onDestroy();
			PostQuitMessage(0);
			break;
		}

		//TODO ?? hwnd is null??
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
		
	}


	RgWindowWindows::RgWindowWindows()
	{
		RgLogD() << "winwindows ctor";
		g_winwindow = this;
	}

	void * RgWindowWindows::getHandler() const
	{
		return m_hWnd;
	}


	void RgWindowWindows::initWindow(RgWindowSettings* settings)
	{
		if (settings == nullptr) {
			RgLogE() << "window settings is null";
			return;
		}
		HINSTANCE hInstance = settings->hInstance;
		if (!hInstance)
			hInstance = (HINSTANCE)GetModuleHandle(nullptr);
		m_hInstance = hInstance;

		WNDCLASS wndClass;
		wndClass.style = CS_DBLCLKS;
		wndClass.lpfnWndProc = RgWindowWindowsWndProc;
		wndClass.cbClsExtra = 0;
		wndClass.cbWndExtra = 0;
		wndClass.hInstance = m_hInstance;
		wndClass.hIcon = settings->hIcon;
		wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wndClass.lpszMenuName = nullptr;
		wndClass.lpszClassName = settings->windowTitle;

		if (!RegisterClass(&wndClass)) {
			RgLogE() << "register windows window error";
			return;
		}

		m_width = 800;
		m_height = 600;

		m_hWnd = CreateWindow(settings->windowTitle, settings->windowTitle, WS_OVERLAPPEDWINDOW, settings->x, settings->y, 800, 600, 0, nullptr, hInstance, 0);
		if (!m_hWnd) {
			RgLogE() << "create windows window error";
			UnregisterClass(settings->windowTitle, m_hInstance);
			return;
		}

		RgLogD() << "winwindow init";
	}
	void RgWindowWindows::releaseWindow()
	{
		std::cout << "winwindows release" << std::endl;
	}
	void RgWindowWindows::showWindow()
	{
		ShowWindow(m_hWnd, SW_SHOW);
		RgLogD() << "winwindows show";
	}
	void RgWindowWindows::closeWindow()
	{
		std::cout << "winwindows close" << std::endl;
		if(m_hWnd != nullptr)
			CloseWindow(m_hWnd);
	}


}


