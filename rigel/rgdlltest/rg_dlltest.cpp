#include "rg_dlltest.h"
#include <sstream>
#include <iostream>
std::string asterisk(int num)
{
	std::ostringstream oss;
	while (num--)
	{
		oss << "*";
	}
	return oss.str();
}

void disp_asterisk(int num)
{
	while (num--)
	{
		std::cout << "*";
	}
	std::cout << std::endl;
}
