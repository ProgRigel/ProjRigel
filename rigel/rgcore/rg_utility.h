#pragma once
#include <string>

namespace rg {
	const std::wstring GetWorkDirectory();
	const std::wstring HrToMessage(HRESULT hr);
	const std::wstring HrToError(HRESULT hr);
}