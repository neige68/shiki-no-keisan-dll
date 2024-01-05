// <test.h> -*- coding: utf-8 -*-
//
// Project try-mathexpr

// Copyright (C) 2023 neige68
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  https://www.boost.org/LICENSE_1_0.txt)

/// \file
/// \brief テスト共通ヘッダ
//
// Compiler: VC14.2
//

#ifndef test_h
#define test_h

//------------------------------------------------------------

/// 許容誤差
//
/// なお IEEE 754 の binary64 のマシンイプシロンは 2.220e-16 だそうだ。
//
/// \todo 5回以上浮動小数点演算を重ねると足りなくなりそうなので検討が必要。
const double epsilon = 1e-15;

/// パーセント単位の許容誤差
//
/// BOOST_CHECK_CLOSE の第3パラメータにパーセント単位で与えるため
const double tolerance_percent = epsilon * 100;

//------------------------------------------------------------

#endif // test_h

// end of <test.h>
