#pragma once

namespace rg {

	class RgWindow;

	class RgWindowWindows : public RgWindow
	{
	public:
		RgWindowWindows();
		~RgWindowWindows();
		void* getHandler() const;
		LRESULT memberWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

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

		LPCWSTR m_pWinClassName = nullptr;
	};

}