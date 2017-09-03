#include "rg_windowWindows.h"
#include <iostream>
namespace rg {
	RgWindowWindows::RgWindowWindows()
	{
		std::cout << "winwindows ctor" << std::endl;
	}
	void RgWindowWindows::InitWindow(RgWindowSettings* settings)
	{
		std::cout << "winwindows init" << std::endl;
	}
	void RgWindowWindows::ReleaseWindow()
	{
		std::cout << "winwindows release" << std::endl;
	}
	void RgWindowWindows::ShowWindow()
	{
		std::cout << "winwindows show" << std::endl;
	}
	void RgWindowWindows::CloseWindow()
	{
		std::cout << "winwindows close" << std::endl;
	}
}


