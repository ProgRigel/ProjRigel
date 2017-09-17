#pragma once
#include <string>

namespace rg {
	const std::wstring GetWorkDirectory();
	const std::string HrToMessage(HRESULT hr);
}