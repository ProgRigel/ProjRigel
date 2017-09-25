#include "rg_dlltest.h"
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
extern "C"
{
	__declspec(dllexport) int asterisk(std::string*meow, int num)
	{
		meow = new std::string;
		while (num--)
		{
			meow->append("*");
		}
		return num;
	}

	__declspec(dllexport) void disp_asterisk(int num)
	{
		while (num--)
		{
			std::cout << "*";
		}
		std::cout << std::endl;
	}
}