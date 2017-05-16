#pragma once
#include "stdafx.h"
#include <vector>
using namespace std;
inline vector<char> WCHAR2CHAR(CString str)
{
	vector<char> path;
	int len = WideCharToMultiByte(CP_ACP, 0, str, str.GetLength(), NULL, 0, NULL, NULL);
	path.resize(len + 1);
	WideCharToMultiByte(CP_ACP, 0, str, str.GetLength(), &path.front(), len, NULL, NULL);
	return path;
}

inline vector<WCHAR> CHAR2WCHAR(const char* str)
{
	vector<WCHAR> Text;
	DWORD dwUnicodeLen;        //转换后Unicode的长       
	dwUnicodeLen = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
	Text.resize(dwUnicodeLen + 1);
	MultiByteToWideChar(CP_ACP, 0, str, -1, &Text.front(), dwUnicodeLen);
	return Text;
}