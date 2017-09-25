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
		RgVec2 v(10, -20);
		v = v + v;
		Check(v.x == 20 && v.y == -41, "RgVec2 + fail");
	}
	//rg_utility.h
	HRESULT hr;
	hr = S_FALSE;
	std::wcout <<"test:HrToMessage:"<< HrToMessage(hr) << std::endl;;
	//rg_dlltest

	typedef void(*DLLFunction)(int);
	DLLFunction dllFunc;
	std::string fun_name("disp_asterisk");
	std::wstring dllpath(L"..\\Debug\\rgdlltest.dll");
	std::wcout << dllpath << std::endl;
	HINSTANCE hInstLibrary = LoadLibrary(dllpath.c_str());
	if (hInstLibrary == NULL)
	{
		std::cout << "no dll loaded" << std::endl;
		FreeLibrary(hInstLibrary);
	}
	else
	{
		dllFunc = (DLLFunction)GetProcAddress(hInstLibrary, fun_name.c_str());
		if (dllFunc == NULL)
		{
			std::cout << "function entry not found" << std::endl;
		}
		else
		{
			dllFunc(20);
		}
		FreeLibrary(hInstLibrary);
	}
	
	RgLogD() << "=================";
	RgLogD() << "Unitest Done!";
	getchar();
	return 0;
}

