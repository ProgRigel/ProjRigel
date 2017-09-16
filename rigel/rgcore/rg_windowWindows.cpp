#pragma once
#include "rgcore.h"
#include "rg_window.h"
#include "rg_windowWindows.h"
namespace rg {

#define GET_X_LPARAM(lp)                        ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp)                        ((int)(short)HIWORD(lp))

	RgWindowWindows *g_winwindow = nullptr;

	LRESULT CALLBACK RgWindowWindowsWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		if(g_winwindow)
			return g_winwindow->memberWndProc(hwnd, uMsg, wParam, lParam);
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}


	RgWindowWindows::RgWindowWindows()
	{
		RgLogD() << "winwindows ctor";
		g_winwindow = this;
	}

	RgWindowWindows::~RgWindowWindows()
	{
		g_winwindow = nullptr;
		RgLogD() << "winwindows dctor";
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

	}
	void RgWindowWindows::showWindow()
	{
		ShowWindow(m_hWnd, SW_SHOW);
	}
	void RgWindowWindows::closeWindow()
	{
		std::cout << "winwindows close" << std::endl;
		if(m_hWnd != nullptr)
			CloseWindow(m_hWnd);
	}

	LRESULT RgWindowWindows::memberWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if (uMsg == WM_KEYDOWN || uMsg == WM_KEYUP || uMsg == WM_SYSKEYDOWN || uMsg == WM_SYSKEYUP) {
			
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
			int mouseButtonState = LOWORD(wParam);

			m_windowInput.LButton = ((mouseButtonState & MK_LBUTTON) != 0);
			m_windowInput.RButton = ((mouseButtonState & MK_RBUTTON) != 0);
			m_windowInput.MButton = ((mouseButtonState & MK_MBUTTON) != 0);

			EventOnMouseButton.emit();
		}
		else if (uMsg == WM_MOUSEWHEEL)
		{
			EventOnMouseWheel.emit(GET_WHEEL_DELTA_WPARAM(wParam));
		}
		else if (uMsg == WM_MOUSEMOVE) {
			EventOnMouseMove.emit(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		}

		switch (uMsg) {
		case WM_PAINT:
			break;
		case WM_SIZE:
			m_width = (UINT)LOWORD(lParam);
			m_height = (UINT)HIWORD(lParam);
			m_resized = true;
			EventOnResize.emit(m_width, m_height);
			EventOnGUI.emit(RgWindowEvent{RgWindowEventType::Resize,&m_windowInput });
			break;
		case WM_ENTERSIZEMOVE:
			EventOnGUI.emit(RgWindowEvent{ RgWindowEventType::ResizeEnter,&m_windowInput });
			EventOnEnterSizeMove.emit();
			break;
		case WM_EXITSIZEMOVE:
			EventOnGUI.emit(RgWindowEvent{ RgWindowEventType::ResizeExit,&m_windowInput });
			EventOnExitSizeMove.emit();
			m_resized = false;
			break;
		case WM_CLOSE:
			EventOnGUI.emit(RgWindowEvent{ RgWindowEventType::Close,&m_windowInput });
			EventOnClose.emit();
			break;
		case WM_DESTROY:
			EventOnDestroy.emit();
			PostQuitMessage(0);
			break;
		}

		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}


}


