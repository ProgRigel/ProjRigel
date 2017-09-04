#pragma once
#include <Windows.h>


namespace rg {

#define RGWINDOW_CALLBACK_DEF(x) RGWINDOW_CALLBACK_##x m_func_##x = nullptr;
#define RGWINDOW_CALLBACK_SETTER(x) void regCallback_##x (RGWINDOW_CALLBACK_##x func){ m_func_##x = func;};
#define RGWINDOW_CALLBACK_FUNC_A(x,a) typedef void(*RGWINDOW_CALLBACK_##x)(RgWindow* win,a);
#define RGWINDOW_CALLBACK_FUNC(x) typedef void(*RGWINDOW_CALLBACK_##x)(RgWindow* win);
	class RgWindow;

	typedef HRESULT(*RGWINDOW_CALLBACK_MSGPROC)(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam);
	typedef void(*RGWINDOW_CALLBACK_FRAME)(double fTime, float fElapsedTime);

	typedef void(*RGWINDOW_CALLBACK_ONCLOSE)(RgWindow* win);
	typedef void(*RGWINDOW_CALLBACK_REGISTER)(RgWindow* win);
	typedef void(*RGWINDOW_CALLBACK_ONRESIZE)(RgWindow* win, unsigned int width, unsigned int height);
	RGWINDOW_CALLBACK_FUNC(ENTER_RESIZE_MOVE);
	RGWINDOW_CALLBACK_FUNC(EXIT_RESIZE_MOVE);
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

		virtual void* getHandler() const = 0;

		virtual void onRegister();
		virtual void onResize(unsigned int width,unsigned int height);
		virtual void onPaint();
		virtual void onEnterSizeMove();
		virtual void onExitSizeMove();
		virtual void onKeyboard();
		virtual void onClose();
		virtual void onDestroy();
		virtual void onMouseButton();
		virtual void onMouseWheel();

		unsigned int getWidth() { return m_width; }
		unsigned int getHeight() { return m_height; }
	protected:
		unsigned int m_width = 0;
		unsigned int m_height = 0;

	private:
		RGWINDOW_CALLBACK_DEF(ONCLOSE)
		RGWINDOW_CALLBACK_DEF(ONRESIZE)
		RGWINDOW_CALLBACK_DEF(REGISTER)
		RGWINDOW_CALLBACK_DEF(MSGPROC)
		RGWINDOW_CALLBACK_DEF(FRAME)

		RGWINDOW_CALLBACK_DEF(ENTER_RESIZE_MOVE)
		RGWINDOW_CALLBACK_DEF(EXIT_RESIZE_MOVE)

	public:

		RGWINDOW_CALLBACK_SETTER(ONCLOSE)
		RGWINDOW_CALLBACK_SETTER(ONRESIZE)
		RGWINDOW_CALLBACK_SETTER(REGISTER)
		RGWINDOW_CALLBACK_SETTER(FRAME)
		RGWINDOW_CALLBACK_SETTER(MSGPROC)

		RGWINDOW_CALLBACK_SETTER(ENTER_RESIZE_MOVE)
		RGWINDOW_CALLBACK_SETTER(EXIT_RESIZE_MOVE)

	public:
		friend class RgWindowManager;
	};

}