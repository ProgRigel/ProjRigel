#pragma once
#include "rg_signal.hpp"

namespace rg {

	class RgWindow;

	typedef HRESULT(*RGWINDOW_CALLBACK_MSGPROC)(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam);
	typedef void(*RGWINDOW_CALLBACK_FRAME)(double fTime, float fElapsedTime);

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

		struct RgWindowInput {
			bool LButton = false;
			bool RButton = false;
			bool MButton = false;
		} m_windowInput;

	protected:
		RgWindow();
		virtual void releaseWindow() = 0;

		void onFrame();
		void onRegister();

	public:
		Signal<void()> EventOnFrame;
		Signal<void()> EventOnRegister;
		Signal<void()> EventOnClose;
		Signal<void()> EventOnDestroy;
		Signal<void()> EventOnEnterSizeMove;
		Signal<void()> EventOnExitSizeMove;
		//width height
		Signal<void(unsigned int,unsigned int)> EventOnResize;
		//mousex mousey
		Signal<void(int, int)> EventOnMouseMove;
		Signal<void(short)> EventOnMouseWheel;
		Signal<void()> EventOnMouseButton;
		
	public:
		virtual void initWindow(RgWindowSettings* settings) = 0;
		virtual void showWindow() = 0;
		virtual void closeWindow() = 0;

		virtual void* getHandler() const = 0;

		unsigned int getWidth() { return m_width; }
		unsigned int getHeight() { return m_height; }
		bool getIsResized() { return m_resized; }

	protected:
		unsigned int m_width = 0;
		unsigned int m_height = 0;
		bool m_resized = false;


		friend class RgWindowManager;
	};

}