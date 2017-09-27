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

	int RgHash(const void * data, int datasize, unsigned int seed)
	{
		static unsigned int crc32_lut[256] = { 0 };
		if (!crc32_lut[1])
		{
			const unsigned int polynomial = 0xEDB88320;
			for (unsigned int i = 0; i < 256; i++)
			{
				unsigned int crc = i;
				for (unsigned int j = 0; j < 8; j++)
					crc = (crc >> 1) ^ (unsigned int(-int(crc & 1)) & polynomial);
				crc32_lut[i] = crc;
			}
		}
		unsigned int crc = seed;
		const unsigned char* current = (const unsigned char*)data;

		if (datasize > 0) {
			while (datasize--)
				crc = (crc >> 8) ^ crc32_lut[(crc & 0xFF) ^ *current++];
		}
		else
		{
			while (unsigned char c = *current++)
			{
				crc = (crc >> 8) ^ crc32_lut[(crc & 0xFF) ^ c];
			}
		}
		return ~crc;
	}

	std::wstring towstring(const std::string & str)
	{
		return std::wstring(str.begin(), str.end());
	}

	std::string tostring(const std::wstring & wstr)
	{
		return std::string(wstr.begin(), wstr.end());
	}

}


