// <charconv.cpp> -*- coding: utf-8 -*-
//
// Project shiki-no-keisan-dll

// Copyright (C) 2024 neige68
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  https://www.boost.org/LICENSE_1_0.txt)

/// \file
/// \brief 文字コード変換
//
// Compiler: VC14.2
//

#include "charconv.h"

#include <windows.h>

#include <vector>

using namespace std;

//------------------------------------------------------------

/// UTF-8 の BOM (Byte Order Mark)
const string utf8bom{"\xEF\xBB\xBF"};

// string から wstring への変換
static
wstring StringToWString(const string& str, UINT cp = CP_ACP)
{
    // 必要なバッファの長さを得る
    int len = MultiByteToWideChar(cp, 0, str.c_str(), -1, nullptr, 0);
    //
    vector<wchar_t> buf(len);
    MultiByteToWideChar(cp, 0, str.c_str(), -1, &buf.at(0), len);
    return wstring(&buf.at(0));
}

// UNICODE から string (コードページ cp) への変換
static
string WideCharToString(const wchar_t* lpMultiByteStr, int cchWideChar = -1, UINT cp = CP_ACP)
{
    // 必要なバッファの長さを得る
    int len = WideCharToMultiByte(cp, 0, lpMultiByteStr, cchWideChar, nullptr, 0, nullptr, nullptr);
    //
    vector<char> buf(len);
    WideCharToMultiByte(cp, 0, lpMultiByteStr, cchWideChar, &buf.at(0), len, nullptr, nullptr);
    return string(&buf.at(0));
}

string to_utf8(const wstring& wstr)
{
    return utf8bom + WideCharToString(wstr.c_str(), -1, CP_UTF8);
}

string to_acp(const wstring& wstr)
{
    return WideCharToString(wstr.c_str());
}

wstring to_wide(const string& str)
{
    if (str.size() >= 3 && str.substr(0, utf8bom.size()) == utf8bom)
        return StringToWString(str.substr(utf8bom.size()), CP_UTF8);
    return StringToWString(str);
}

//------------------------------------------------------------

// end of <charconv.cpp>
