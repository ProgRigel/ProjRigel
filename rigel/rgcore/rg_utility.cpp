#pragma once
#include "rgcore.h"
#include "rg_utility.h"
namespace rg {

	const std::wstring GetWorkDirectory()
	{
		static bool pathgot = false;
		static std::wstring workpath = L"";
		if (pathgot == false) {
			WCHAR buf[512];
			GetCurrentDirectory(512, buf);
			workpath = std::wstring(buf);
			//std::wcout << "[workpath]" << workpath << std::endl;
			pathgot = true;
		}

		return workpath;
	}
	const std::string HrToMessage(HRESULT hr)
	{
		LPVOID lpMsgBuf;
		::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			hr,
			MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf,
			0,
			NULL);
		std::string meow;
		meow.append((char*)lpMsgBuf);
		::LocalFree(lpMsgBuf);
		return meow;
	}
}


