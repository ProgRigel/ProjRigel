#include <exception>
#include <functional>
#include <string>

struct RgTestSuit {
	std::wstring Title;
	std::wstring Description;
	std::function<bool()> TestFunction;

	RgTestSuit(std::wstring title_, std::wstring description_, std::function<bool()> func_) :Title(title_), Description(description_), TestFunction(func_){}
};

void RegisterTestSuit(const RgTestSuit& testsuit);