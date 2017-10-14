
#include <rgcore\rgcore.h>

using namespace rg;

static int count = 0;

void test(){
	if (count > 100) {

		RgWindowManager::ReleaseWindow();
	}

	count++;
}

int main() {

	RgWindow * win = nullptr;

	RgWindowSettings set;
	set.windowTitle = L"testWindow";

	RgWindowManager::CreateWindowWithSettings(&win, &set);
	win->Show();
	//win->EventOnFrame.connect<&test>();
	RgWindowManager::EnterRunLoop(10);



	getchar();

	return 0;
}