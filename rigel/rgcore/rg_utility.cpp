#pragma once
#include "rgcore.h"
namespace rg {

	const std::wstring GetWorkDirectory()
	{
		static bool pathgot = false;
		static std::wstring workpath = L"";
		if (pathgot == false) {
			WCHAR buf[512];
			GetCurrentDirectory(512, buf);
			workpath = std::wstring(buf);
			std::wcout << "[workpath]" << workpath << std::endl;
			pathgot = true;
		}

		return workpath;
	}
}


