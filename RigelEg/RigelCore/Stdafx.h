// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once
#include <Windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <iostream>
#include <vcclr.h>
#include <map>

#include <msclr\auto_gcroot.h>
#include <msclr\marshal_cppstd.h>

void DebugLog(const char* msg);
void DebugLog(System::String ^ msg);