#include "rgtest_rgcore.h"
#include "rgtest.h"
#include <rgcore\rgcore.h>
#include <chrono>

using namespace rg;

void AddRgCoreTestSuits()
{
	RegisterTestSuit(RgTestSuit(L"CreateWindow",L"test for window creation", []() {
		RgWindow * win = nullptr;

		RgWindowSettings set;
		set.windowTitle = L"CreateWindowTest";
		RgWindowManager::CreateWindowWithSettings(&win, &set);
		win->Show();

		static auto testOnFrame = []() {
			static int count = 0;
			if (count > 100) {
				RgWindowManager::ReleaseWindow();
			}
			count++;
		};
		win->EventOnFrame.connect(testOnFrame);
		RgWindowManager::EnterRunLoop(10);

		return true;
	}));
}
