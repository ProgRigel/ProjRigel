#pragma once
#include <string>
#include "rg_math.h"

namespace rg {
	const std::wstring GetWorkDirectory();
	const std::wstring HrToMessage(HRESULT hr);
	const std::wstring HrToError(HRESULT hr);
	inline unsigned int HR_CODE(HRESULT hr) {
		return hr &(0xFFFF);
	}

	int RgHash(const void* data, int datasize, unsigned int seed = 0);

	std::wstring towstring(const std::string& str);
	std::string tostring(const std::wstring& wstr);

	RgVec4 ColorRGB(byte r,byte g,byte b,byte a);

}