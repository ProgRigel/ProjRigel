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
	class RgLogger
	{
	public:
		RgLogger(const char * file, const char * function, int line);
		~RgLogger();
	public:
		RgLogger& Debug();
		RgLogger& Warning();
		RgLogger& Error();

	public:

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
