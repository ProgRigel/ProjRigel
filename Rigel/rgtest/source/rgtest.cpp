
#include <rgcore\rgcore.h>
#include "..\include\rgtest.h"
#include <vector>
#include "rgtest_rgcore.h"

using namespace rg;
std::vector<RgTestSuit> g_testsuits;

void RunTestSuit() {

	for (auto iter = g_testsuits.begin();iter != g_testsuits.end(); iter++)
	{
		bool result = false;
		try
		{
			result = (*iter).TestFunction();
		}
		catch (const std::exception& e)
		{

			RgLogW("Exception") << RgLogStyle::Yello << (*iter).Title << e.what();
			continue;
		}

		if (result) {
			RgLogW("Success") << RgLogStyle::Green << (*iter).Title;
		}
		else {
			RgLogW("Fail") << RgLogStyle::Red << (*iter).Title;
		}
		

	}
}



int main() {

	AddRgCoreTestSuits();

	RgLogD() << "---------------------";

	RunTestSuit();


	getchar();


	return 0;
}

void RegisterTestSuit(const RgTestSuit & testsuit)
{
	g_testsuits.push_back(testsuit);
}
