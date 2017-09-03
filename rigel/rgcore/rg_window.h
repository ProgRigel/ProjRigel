#pragma once
#include <Windows.h>


namespace rg {

	typedef HRESULT(*RGWINDOW_CALLBACK_MSGPROC)(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam);
	typedef void(*RGWINDOW_CALLBACK_NEWFRAME)(double fTime, float fElapsedTime);

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
		virtual void ReleaseWindow() = 0;

	public:
		virtual void InitWindow(RgWindowSettings* settings) = 0;
		virtual void ShowWindow() = 0;
		virtual void CloseWindow() = 0;

	private:
		RGWINDOW_CALLBACK_MSGPROC m_funcMsgProc;
		RGWINDOW_CALLBACK_NEWFRAME m_funcNewframe;
	public:
		void regCallbackMsgProc(RGWINDOW_CALLBACK_MSGPROC func);
		void regCallbackNewFrame(RGWINDOW_CALLBACK_NEWFRAME func);

	public:
		friend class RgWindowManager;
	};


	

	HRESULT RgWindowCreateWindow(RgWindow** pwindow, RgWindowSettings* windowSettings);
}