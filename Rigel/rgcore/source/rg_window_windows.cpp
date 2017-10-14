#pragma once
#include "rgcore.h"
#include "rg_window.h"
#include "rg_window_windows.h"
namespace rg {

#define GET_X_LPARAM(lp)                        ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp)                        ((int)(short)HIWORD(lp))


	LRESULT CALLBACK RgWindowWindowsWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

		if (hwnd == nullptr) {
			RgLogW() << "null hwnd";
		}

		auto mainwin = RgWindowManager::GetMainWindow();
		if (mainwin != nullptr) {
			if (hwnd == mainwin->getHandler()) {
				RgWindowWindows * winWindows = dynamic_cast<RgWindowWindows *>(mainwin);
				return winWindows->memberWndProc(hwnd, uMsg, wParam, lParam);
			}
		}

		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}


	RgWindowWindows::RgWindowWindows()
	{
		m_hWnd = 0;
	}

	RgWindowWindows::~RgWindowWindows()
	{
		if (m_hWnd != nullptr) m_hWnd = nullptr;
		if (m_hInstance != nullptr) {
			UnregisterClass(m_pWinClassName, m_hInstance);
			m_hInstance = nullptr;
			RgLogD()<< RgLogStyle::Cyan << "release window class";
		}
		RgLogD() << "dctor window windows";
	}

	void * RgWindowWindows::getHandler() const
	{
		return m_hWnd;
	}


	void RgWindowWindows::InitWindow(RgWindowSettings* settings)
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

		m_pWinClassName = settings->windowTitle;

		if (!RegisterClass(&wndClass)) {
			RgLogE() << "register windows window error";
			return;
		}

		m_width = 800;
		m_height = 600;

		m_bIsChild = false;
		m_destroyed = false;

		RgWindowManager::InternalRegisterWindow(this);

		m_hWnd = CreateWindow(settings->windowTitle, settings->windowTitle, WS_OVERLAPPEDWINDOW, settings->x, settings->y, 800, 600, 0, nullptr, hInstance, 0);
		if (!m_hWnd) {
			RgLogE() << "create windows window error";
			UnregisterClass(settings->windowTitle, m_hInstance);
			return;
		}
		else{
			RgLogD() << "create windows window success";
		}
		

		RgLogD() << "winwindow init";
	}
	void RgWindowWindows::Destroy()
	{
		//send WM_DESTROY
		if(m_hWnd != nullptr)
			DestroyWindow(m_hWnd);
	}
	void RgWindowWindows::Show()
	{
		ShowWindow(m_hWnd, SW_SHOW);
	}
	void RgWindowWindows::Close()
	{
		//send WM_CLOSE
		CloseWindow(m_hWnd);
	}

	LRESULT RgWindowWindows::memberWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if (uMsg == WM_KEYDOWN || uMsg == WM_KEYUP || uMsg == WM_SYSKEYDOWN || uMsg == WM_SYSKEYUP) {

			bool iskeydown = (uMsg == WM_KEYDOWN || WM_SYSKEYDOWN);
			m_windowInput.AltDown = ((lParam & (1 << 29)) != 0);
			m_windowInput.KeyCode[(byte)(wParam & 0xFF)] = iskeydown;

			EventOnGUI.emit(RgWindowEvent{ RgWindowEventType::KeyEvent,&m_windowInput });
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
			EventOnGUI.emit(RgWindowEvent{ RgWindowEventType::MouseEvent,&m_windowInput });

		}
		else if (uMsg == WM_MOUSEWHEEL)
		{
			EventOnMouseWheel.emit(GET_WHEEL_DELTA_WPARAM(wParam));
			EventOnGUI.emit(RgWindowEvent{ RgWindowEventType::MouseWheelEvent,&m_windowInput });
		}
		else if (uMsg == WM_MOUSEMOVE) {
			int mousex = GET_X_LPARAM(lParam);
			int mousey = GET_Y_LPARAM(lParam);
			EventOnMouseMove.emit(mousex,mousey );
			m_windowInput.MousePos = RgVec2((float)mousex, (float)mousey);
			EventOnGUI.emit(RgWindowEvent{ RgWindowEventType::MouseMove,&m_windowInput });
		}

		switch (uMsg) {
		case WM_PAINT:
			break;
		case WM_SIZE:
			m_width = (UINT)LOWORD(lParam);
			m_height = (UINT)HIWORD(lParam);
			m_resized = true;
			m_windowInput.WindowRect.z = static_cast<float>(m_width);
			m_windowInput.WindowRect.w = static_cast<float>(m_height);
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

			Destroy();
			break;
		case WM_DESTROY:
			EventOnDestroy.emit();

			RgLogD() << RgLogStyle::Cyan << "window destroy";

			m_hWnd = nullptr;
			m_destroyed = true;
			break;
		}

		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}


}


