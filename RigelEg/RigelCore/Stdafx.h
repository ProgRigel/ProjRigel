// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

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