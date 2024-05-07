// <double_parser.cpp> -*- coding: utf-8 -*-
//
// Project shiki-no-keisan-dll

// Copyright (C) 2024 neige68
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  https://www.boost.org/LICENSE_1_0.txt)

/// \file
/// \brief 精度を改善した double (倍精度浮動小数点) パーサ
//
// Compiler: VC14.2
//

#include "double_parser.h"

#include <string>               // std::wstring

//------------------------------------------------------------

namespace my_parser {

thread_local std::wstring::const_iterator my_double_start;

} // namespace my_parser

//------------------------------------------------------------

// end of <double_parser.cpp>
