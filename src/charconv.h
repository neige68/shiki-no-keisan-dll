// <charconv.h> -*- coding: utf-8 -*-
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

#ifndef charconv_h
#define charconv_h

#include <string>

//------------------------------------------------------------

/// wstring を BOM 付き UTF-8 文字列に変換
std::string to_utf8(const std::wstring& wstr);

/// wstring をアクティブコードページ ナロー文字列に変換
std::string to_acp(const std::wstring& wstr);

/// BOM を判定して UTF-8 またはアクティブコードページ ナロー文字列を wstring に変換
std::wstring to_wide(const std::string& str);

//------------------------------------------------------------

#endif // charconv_h

// end of <charconv.h>
