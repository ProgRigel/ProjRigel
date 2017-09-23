#pragma once
#include <string>

namespace rg {
	const std::wstring GetWorkDirectory();
	const std::wstring HrToMessage(HRESULT hr);
	const std::wstring HrToError(HRESULT hr);
	inline unsigned int HR_CODE(HRESULT hr) {
		return hr &(0xFFFF);
	}

	int RgHash(const void* data, int datasize, unsigned int seed = 0);
}