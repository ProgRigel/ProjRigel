#pragma once
#include <Windows.h>


namespace rg {

#define RGWINDOW_CALLBACK_DEF(x) RGWINDOW_CALLBACK_##x m_func##x;
#define RGWINDOW_CALLBACK_SETTER(x) inline void regCallback##x (RGWINDOW_CALLBACK_##x func){ m_func##x = func;};

	class RgWindow;

	typedef HRESULT(*RGWINDOW_CALLBACK_MSGPROC)(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam);
	typedef void(*RGWINDOW_CALLBACK_FRAME)(double fTime, float fElapsedTime);

	typedef void(*RGWINDOW_CALLBACK_ONCLOSE)(RgWindow* win);
	typedef void(*RGWINDOW_CALLBACK_ONCREATE)(RgWindow* win);

	struct RgWindowSettings
	{
		const WCHAR* windowTitle = L"RgWindow";
		HINSTANCE hInstance = nullptr;
		HICON hIcon = nullptr;
		int x = CW_USEDEFAULT;
		int y = CW_USEDEFAULT;
	};

	class RgWindow
	{
	protected:
		virtual ~RgWindow();
		RgWindow(const RgWindow&) = delete;
		RgWindow& operator=(const RgWindow&) = delete;

	protected:
		RgWindow();
		virtual void releaseWindow() = 0;

		
	public:
		virtual void initWindow(RgWindowSettings* settings) = 0;
		virtual void showWindow() = 0;
		virtual void closeWindow() = 0;

		virtual void onResize();
		virtual void onPaint();
		virtual void onEnterSizeMove();
		virtual void onExitSizeMove();
		virtual void onKeyboard();
		virtual void onClose();
		virtual void onDestroy();
		virtual void onMouseButton();
		virtual void onMouseWheel();

	private:
		RGWINDOW_CALLBACK_DEF(ONCLOSE)
		RGWINDOW_CALLBACK_DEF(ONCREATE)
		RGWINDOW_CALLBACK_DEF(MSGPROC)
		RGWINDOW_CALLBACK_DEF(FRAME)
	public:

		RGWINDOW_CALLBACK_SETTER(ONCLOSE)
		RGWINDOW_CALLBACK_SETTER(ONCREATE)
		RGWINDOW_CALLBACK_SETTER(FRAME)
		RGWINDOW_CALLBACK_SETTER(MSGPROC)

	public:
		friend class RgWindowManager;
	};


	

	HRESULT RgWindowCreateWindow(RgWindow** pwindow, RgWindowSettings* windowSettings);
}