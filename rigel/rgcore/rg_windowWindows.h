#pragma once
#include "rg_window.h"

namespace rg {

	class RgWindow;

	class RgWindowWindows : public RgWindow
	{
	public:
		RgWindowWindows();
		
	protected:
		
		void ReleaseWindow();
	public:
		void InitWindow(RgWindowSettings* settings);
		void ShowWindow();
		void CloseWindow();

	private:
		RgWindowWindows(const RgWindowWindows&) = delete;
		RgWindowWindows& operator=(const RgWindowWindows&) = delete;
	};

}