#pragma once
#include <rgengine\rgengine.h>
#include <common\common.h>
#include <common\entry\entry.h>
#include <common\bgfx_utils.h>
#include <filesystem>
#include <iostream>
#include <string>

#include "rgeditor_module.h"
#include "rgeditor_core.h"

#define RGLOG_DEBUG(x) rgeditor::RgEditorModuleConsole::logDebug(x)

inline std::wstring RG_STR2WSTR(const std::string& str)
{
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.from_bytes(str);
}

inline std::string RG_WSTR2STR(const std::wstring& wstr)
{
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.to_bytes(wstr);
}