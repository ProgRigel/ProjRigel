#include <Windows.h>
#include <rgcore\rgcore.h>
#include <rggraphics\rg_graphicsAPI.h>
#include <rggui\rg_gui.h>
#include <rgcore\rg_utility.h>
using namespace rg;

#define Check(h,l) if((h) == false) RgLogW()<<l;

int main() {

	RgLogD() << "Start Unitest";
	RgLogD() << "=================";
	//rg_math.h
	{
		RgVec2<RgFloat> v(10, -20);
		v = v + v;
		Check(v.x == 20 && v.y == -41, "RgVec2 + fail");
	}
	//rg_utility.h
	HRESULT hr;
	hr = S_FALSE;
	std::wcout <<"test:HrToMessage:"<< HrToMessage(hr) << std::endl;;

	RgLogD() << "=================";
	RgLogD() << "Unitest Done!";
	getchar();
	return 0;
}

