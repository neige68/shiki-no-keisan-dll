// <test_sign.cpp> -*- coding: utf-8 -*-
//
// Project try-mathexpr

// Copyright (C) 2023 neige68
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  https://www.boost.org/LICENSE_1_0.txt)

/// \file
/// \brief sign, abs, mod のテスト
//
// Compiler: VC14.2
//

#define BOOST_TEST_MODULE TestSign
#include <boost/test/unit_test.hpp>

#include "test.h"
#include "shiki_no_keisan.h"

#include <cmath>
#include <limits>

using namespace std;
using namespace std::string_literals;

//------------------------------------------------------------
//
// sign
//

BOOST_AUTO_TEST_CASE(test_sign_inf)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"sign(inf)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 1);
}

BOOST_AUTO_TEST_CASE(test_sign_zero)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"sign(0)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 0);
}

BOOST_AUTO_TEST_CASE(test_sign_neg_inf)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"sign(-inf)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == -1);
}

//------------------------------------------------------------
//
// abs
//

BOOST_AUTO_TEST_CASE(test_abs_inf)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"abs(inf)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == numeric_limits<double>::infinity());
}

BOOST_AUTO_TEST_CASE(test_abs_zero)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"abs(0)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 0);
}

BOOST_AUTO_TEST_CASE(test_abs_neg_inf)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"abs(-inf)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == numeric_limits<double>::infinity());
}

//------------------------------------------------------------
//
// mod
//

/// この計算は 89.3-88.0=1.3 であり、89.3 は 1.3 の約 69 倍であるので
/// 桁落ちし、マシンイプシロン 2.220e-16 の 69 倍 である 1.532e-14 程
/// 度の誤差が生じる
BOOST_AUTO_TEST_CASE(test_mod)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"mod(89.3, 2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, 1.3, 1.54e-14 * 100);
}

BOOST_AUTO_TEST_CASE(test_mod_neg)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"mod(-89.3, 2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, -1.3, 1.54e-14 * 100);
}

BOOST_AUTO_TEST_CASE(test_mod_neg_neg)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"mod(-89.3, -2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, -1.3, 1.54e-14 * 100);
}

BOOST_AUTO_TEST_CASE(test_mod_inf)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"mod(inf, 2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(isnan(r));
}

BOOST_AUTO_TEST_CASE(test_mod_2_inf)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"mod(2, inf)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 2);
}

//------------------------------------------------------------

// end of <test_sign.cpp>
