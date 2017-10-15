#pragma once
#include "rg_inc.h"

#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <Windows.h>


#define RgLogD rg::RgLogger(__FILE__,__FUNCTION__,__LINE__).Debug
#define RgLogW rg::RgLogger(__FILE__,__FUNCTION__,__LINE__).Warning
#define RgLogE rg::RgLogger(__FILE__,__FUNCTION__,__LINE__).Error


namespace rg
{
	enum class RgLogStyle {
		Yello = FOREGROUND_RED | FOREGROUND_GREEN,
		Cyan = FOREGROUND_GREEN | FOREGROUND_BLUE,
		Magenta = FOREGROUND_RED | FOREGROUND_BLUE,
		Red = FOREGROUND_RED | FOREGROUND_INTENSITY,
		Green = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
		Blue = FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	};

	class RgLogger
	{
	public:
		RgLogger(const char * file, const char * function, int line);
		~RgLogger();
	public:
		RgLogger& Debug(const char* prefix = nullptr);
		RgLogger& Warning(const char* prefix = nullptr);
		RgLogger& Error(const char* prefix = nullptr);

	public:

		inline RgLogger& operator << (const RgLogStyle& style) {
			SetConsoleTextAttribute(m_Stdout, (WORD)style);
			return *this;
		}

		inline RgLogger& operator <<(const char * v)
		{
			m_sstream << v;
			return space();
		}
		inline RgLogger & operator <<(std::string v)
		{
			std::wstring wstr(v.length(), L' ');
			std::copy(v.begin(), v.end(), wstr.begin());
			m_sstream << wstr;
			return space();
		}
		inline RgLogger& operator <<(const WCHAR* v)
		{
			m_sstream << v;
			return space();
		}
		inline RgLogger& operator <<(std::wstring v)
		{
			m_sstream << v;
			return space();
		}
		inline RgLogger& operator <<(int v)
		{
			m_sstream << v;
			return space();
		}
		inline RgLogger& operator <<(unsigned short t)
		{
			m_sstream << t;
			return space();
		}
		inline RgLogger& operator <<(char t)
		{
			m_sstream << t;
			return space();
		}
		inline RgLogger& operator<<(unsigned int t)
		{
			m_sstream << t;
			return space();
		}
		inline RgLogger& operator<<(long t)
		{
			m_sstream << t;
			return space();
		}
		inline RgLogger& operator<<(float t)
		{
			m_sstream << t;
			return space();
		}
		inline RgLogger& operator<<(double t)
		{
			m_sstream << t;
			return space();
		}
		inline RgLogger& operator<<(unsigned long t)
		{
			m_sstream << t;
			return space();
		}

		inline RgLogger& operator<<(unsigned long long t) {
			m_sstream << t;
			return space();
		}

		inline RgLogger& space()
		{
			m_sstream << ' ';
			return *this;
		}

	private:
		std::wstringstream m_sstream;
		const char * m_file;
		const char * m_func;
		int m_line;

		HANDLE m_Stdout;
	};
}
