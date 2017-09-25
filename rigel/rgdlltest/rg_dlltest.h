#pragma once
#include <string>
extern "C"
{
	__declspec(dllexport) int asterisk(std::string*meow, int num);
	__declspec(dllexport) void disp_asterisk(int num);
}