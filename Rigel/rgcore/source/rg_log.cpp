#pragma once
#include "rgcore.h"
#include "rg_log.h"
namespace rg
{
	RgLogger::RgLogger(const char * file, const char * function, int line) : m_line(line), m_file(file), m_func(function)
	{
		m_Stdout = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	RgLogger::~RgLogger()
	{
		std::wcout << m_sstream.str() << "       " << m_file << ' ' << m_func << " line: " << m_line << std::endl;
		SetConsoleTextAttribute(m_Stdout, FOREGROUND_INTENSITY);
	}

	RgLogger & RgLogger::Debug(const char* prefix)
	{
		SetConsoleTextAttribute(m_Stdout, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		m_sstream << '[' << (prefix == nullptr ? "Debug" : prefix) << "] " ;
		return *this;
	}
	RgLogger & RgLogger::Warning(const char* prefix)
	{
		SetConsoleTextAttribute(m_Stdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		m_sstream << '[' << (prefix == nullptr ? "Warning" : prefix) << "] ";
		return *this;
	}
	RgLogger & RgLogger::Error(const char* prefix)
	{
		SetConsoleTextAttribute(m_Stdout, FOREGROUND_RED | FOREGROUND_INTENSITY);
		m_sstream << '[' << (prefix == nullptr ? "Error" : prefix) << "] ";
		return *this;
	}
}

