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
	const std::wstring HrToMessage(HRESULT hr)
	{
		LPTSTR lpMsgBuf=NULL;
		::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM| FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			hr,
			MAKELANGID(LANG_ENGLISH,SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf,
			0,
			NULL);
		if (lpMsgBuf != NULL)
		{
			std::wstring meow;
			meow.append((wchar_t*)lpMsgBuf);
			::LocalFree(lpMsgBuf);
			return meow;
		}
		return std::wstring();
	}

	const std::wstring HrToError(HRESULT hr)
	{
		_com_error error(hr);
		LPCTSTR errorText = error.ErrorMessage();
		std::wstring w_err((wchar_t*)errorText);
		return w_err;
	}

}


