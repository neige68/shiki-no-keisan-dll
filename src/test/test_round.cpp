// <test_round.cpp> -*- coding: utf-8 -*-
//
// Project shiki-no-keisan-dll

// Copyright (C) 2024 neige68
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  https://www.boost.org/LICENSE_1_0.txt)

/// \file
/// \brief 端数調整のテスト
//
// Compiler: VC14.2
//

#define BOOST_TEST_MODULE TestRound
#include <boost/test/unit_test.hpp>

#include "test.h"
#include "shiki_no_keisan.h"

#include <cmath>
#include <limits>

using namespace std;
using namespace std::string_literals;

//------------------------------------------------------------
//
// floor
//

BOOST_AUTO_TEST_CASE(test_floor_zero)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    double r = SHIKI_NO_KEISAN_Eval(L"floor(0)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 0);
    r = SHIKI_NO_KEISAN_Eval(L"floor(1-2e-15)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 0);
    r = SHIKI_NO_KEISAN_Eval(L"floor(-0.5e-15)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 0);
}

BOOST_AUTO_TEST_CASE(test_floor_one)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    double r = SHIKI_NO_KEISAN_Eval(L"floor(1)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 1);
    r = SHIKI_NO_KEISAN_Eval(L"floor(2-3e-15)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 1);
    r = SHIKI_NO_KEISAN_Eval(L"floor(1-0.5e-15)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 1);
}

BOOST_AUTO_TEST_CASE(test_floor_neg_one)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    double r = SHIKI_NO_KEISAN_Eval(L"floor(-1)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == -1);
    r = SHIKI_NO_KEISAN_Eval(L"floor(-2e-15)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == -1);
    r = SHIKI_NO_KEISAN_Eval(L"floor(-1-0.5e-15)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == -1);
}

BOOST_AUTO_TEST_CASE(test_floor_two)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    double r = SHIKI_NO_KEISAN_Eval(L"floor(2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 2);
    r = SHIKI_NO_KEISAN_Eval(L"floor(3-4e-15)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 2);
    r = SHIKI_NO_KEISAN_Eval(L"floor(2-1.5e-15)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 2);
}

BOOST_AUTO_TEST_CASE(test_floor_neg_two)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    double r = SHIKI_NO_KEISAN_Eval(L"floor(-2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == -2);
    r = SHIKI_NO_KEISAN_Eval(L"floor(-1-2e-15)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == -2);
    r = SHIKI_NO_KEISAN_Eval(L"floor(-2-1.5e-15)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == -2);
}

BOOST_AUTO_TEST_CASE(test_floor_inf)
{
    const double r = SHIKI_NO_KEISAN_Eval(L"floor(inf)");
    BOOST_CHECK(r == numeric_limits<double>::infinity());
}

BOOST_AUTO_TEST_CASE(test_floor_neg_inf)
{
    const double r = SHIKI_NO_KEISAN_Eval(L"floor(-inf)");
    BOOST_CHECK(r == -numeric_limits<double>::infinity());
}

BOOST_AUTO_TEST_CASE(test_floor_10to15p)
{
    double r = SHIKI_NO_KEISAN_Eval(L"floor(1e15)");
    BOOST_CHECK(r == 1e15);
    r = SHIKI_NO_KEISAN_Eval(L"floor(-1e15)");
    BOOST_CHECK(r == -1e15);
}

//------------------------------------------------------------
//
// ceil
//

BOOST_AUTO_TEST_CASE(test_ceil_zero)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    double r = SHIKI_NO_KEISAN_Eval(L"ceil(0)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 0);
    r = SHIKI_NO_KEISAN_Eval(L"ceil(0.5e-15)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 0);
    r = SHIKI_NO_KEISAN_Eval(L"ceil(-1+2e-15)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 0);
}

BOOST_AUTO_TEST_CASE(test_ceil_one)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    double r = SHIKI_NO_KEISAN_Eval(L"ceil(1)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 1);
    r = SHIKI_NO_KEISAN_Eval(L"ceil(1+0.5e-15)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 1);
    r = SHIKI_NO_KEISAN_Eval(L"ceil(2e-15)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 1);
}

BOOST_AUTO_TEST_CASE(test_ceil_neg_one)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    double r = SHIKI_NO_KEISAN_Eval(L"ceil(-1)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == -1);
    r = SHIKI_NO_KEISAN_Eval(L"ceil(-1+0.5e-15)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == -1);
    r = SHIKI_NO_KEISAN_Eval(L"ceil(-2+3e-15)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == -1);
}

BOOST_AUTO_TEST_CASE(test_ceil_two)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    double r = SHIKI_NO_KEISAN_Eval(L"ceil(2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 2);
    r = SHIKI_NO_KEISAN_Eval(L"ceil(2+1.5e-15)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 2);
    r = SHIKI_NO_KEISAN_Eval(L"ceil(2-1.5e-15)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 2);
}

BOOST_AUTO_TEST_CASE(test_ceil_neg_two)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    double r = SHIKI_NO_KEISAN_Eval(L"ceil(-2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == -2);
    r = SHIKI_NO_KEISAN_Eval(L"ceil(-2-1.5e-15)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == -2);
    r = SHIKI_NO_KEISAN_Eval(L"ceil(-3+3.5e-15)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == -2);
}

BOOST_AUTO_TEST_CASE(test_ceil_inf)
{
    const double r = SHIKI_NO_KEISAN_Eval(L"ceil(inf)");
    BOOST_CHECK(r == numeric_limits<double>::infinity());
}

BOOST_AUTO_TEST_CASE(test_ceil_neg_inf)
{
    const double r = SHIKI_NO_KEISAN_Eval(L"ceil(-inf)");
    BOOST_CHECK(r == -numeric_limits<double>::infinity());
}

BOOST_AUTO_TEST_CASE(test_ceil_10to15p)
{
    double r = SHIKI_NO_KEISAN_Eval(L"ceil(1e15)");
    BOOST_CHECK(r == 1e15);
    r = SHIKI_NO_KEISAN_Eval(L"ceil(-1e15)");
    BOOST_CHECK(r == -1e15);
}

//------------------------------------------------------------
//
// trunc
//

BOOST_AUTO_TEST_CASE(test_trunc_zero)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    double r = SHIKI_NO_KEISAN_Eval(L"trunc(0)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 0);
    r = SHIKI_NO_KEISAN_Eval(L"trunc(1-1.5e-15)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 0);
    r = SHIKI_NO_KEISAN_Eval(L"trunc(-1+1.5e-15)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 0);
}

BOOST_AUTO_TEST_CASE(test_trunc_one)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    double r = SHIKI_NO_KEISAN_Eval(L"trunc(1)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 1);
    r = SHIKI_NO_KEISAN_Eval(L"trunc(2-2.5e-15)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 1);
    r = SHIKI_NO_KEISAN_Eval(L"trunc(1-0.5e-15)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 1);
}

BOOST_AUTO_TEST_CASE(test_trunc_neg_one)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    double r = SHIKI_NO_KEISAN_Eval(L"trunc(-1)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == -1);
    r = SHIKI_NO_KEISAN_Eval(L"trunc(-1+0.5e-15)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == -1);
    r = SHIKI_NO_KEISAN_Eval(L"trunc(-2+2.5e-15)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == -1);
}

BOOST_AUTO_TEST_CASE(test_trunc_two)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    double r = SHIKI_NO_KEISAN_Eval(L"trunc(2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 2);
    r = SHIKI_NO_KEISAN_Eval(L"trunc(3-3.5e-15)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 2);
    r = SHIKI_NO_KEISAN_Eval(L"trunc(2-1.5e-15)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 2);
}

BOOST_AUTO_TEST_CASE(test_trunc_neg_two)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    double r = SHIKI_NO_KEISAN_Eval(L"trunc(-2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == -2);
    r = SHIKI_NO_KEISAN_Eval(L"trunc(-2+1.5e-15)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == -2);
    r = SHIKI_NO_KEISAN_Eval(L"trunc(-3+3.5e-15)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == -2);
}

BOOST_AUTO_TEST_CASE(test_trunc_inf)
{
    const double r = SHIKI_NO_KEISAN_Eval(L"trunc(inf)");
    BOOST_CHECK(r == numeric_limits<double>::infinity());
}

BOOST_AUTO_TEST_CASE(test_trunc_neg_inf)
{
    const double r = SHIKI_NO_KEISAN_Eval(L"trunc(-inf)");
    BOOST_CHECK(r == -numeric_limits<double>::infinity());
}

BOOST_AUTO_TEST_CASE(test_trunc_10to15p)
{
    double r = SHIKI_NO_KEISAN_Eval(L"trunc(1e15)");
    BOOST_CHECK(r == 1e15);
    r = SHIKI_NO_KEISAN_Eval(L"trunc(-1e15)");
    BOOST_CHECK(r == -1e15);
}

//------------------------------------------------------------
//
// rounddown
//

BOOST_AUTO_TEST_CASE(test_rounddown_posi_def)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"rounddown(123.45)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 123);
}

BOOST_AUTO_TEST_CASE(test_rounddown_posi_zero)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"rounddown(123.45, 0)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 123);
}

BOOST_AUTO_TEST_CASE(test_rounddown_one)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"rounddown(123.45, 1)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, 123.4, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_rounddown_posi_one)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"rounddown(123.45, -1)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 120);
}

BOOST_AUTO_TEST_CASE(test_rounddown_neg_posi_def)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"rounddown(-123.45)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == -123);
}

BOOST_AUTO_TEST_CASE(test_rounddown_neg_posi_zero)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"rounddown(-123.45, 0)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == -123);
}

BOOST_AUTO_TEST_CASE(test_rounddown_neg_one)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"rounddown(-123.45, 1)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, -123.4, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_rounddown_neg_posi_one)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"rounddown(-123.45, -1)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == -120);
}

BOOST_AUTO_TEST_CASE(test_rounddown_minus_two)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"rounddown(123.45*(1-5e-16), 2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, 123.45, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_rounddown_neg_plus_two)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"rounddown(-123.45*(1+5e-16), 2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, -123.45, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_rounddown_inf_two)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"rounddown(inf, 2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == numeric_limits<double>::infinity());
}

BOOST_AUTO_TEST_CASE(test_rounddown_10to15p)
{
    double r = SHIKI_NO_KEISAN_Eval(L"rounddown(1e15)");
    BOOST_CHECK(r == 1e15);
    r = SHIKI_NO_KEISAN_Eval(L"rounddown(-1e15)");
    BOOST_CHECK(r == -1e15);
}

//------------------------------------------------------------
//
// roundup
//

BOOST_AUTO_TEST_CASE(test_roundup_posi_def)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"roundup(123.45)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 124);
}

BOOST_AUTO_TEST_CASE(test_roundup_posi_zero)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"roundup(123.45, 0)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 124);
}

BOOST_AUTO_TEST_CASE(test_roundup_one)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"roundup(123.45, 1)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, 123.5, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_roundup_posi_one)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"roundup(123.45, -1)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 130);
}

BOOST_AUTO_TEST_CASE(test_roundup_neg_posi_def)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"roundup(-123.45)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == -124);
}

BOOST_AUTO_TEST_CASE(test_roundup_neg_posi_zero)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"roundup(-123.45, 0)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == -124);
}

BOOST_AUTO_TEST_CASE(test_roundup_neg_one)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"roundup(-123.45, 1)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, -123.5, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_roundup_neg_posi_one)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"roundup(-123.45, -1)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == -130);
}

BOOST_AUTO_TEST_CASE(test_roundup_plus_two)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"roundup(123.45*(1+5e-16), 2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, 123.45, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_roundup_minus_two)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"roundup(123.45*(1-5e-16), 2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, 123.45, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_roundup_neg_plus_two)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"roundup(-123.45*(1+5e-16), 2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, -123.45, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_roundup_neg_minus_two)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"roundup(-123.45*(1-5e-16), 2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, -123.45, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_roundup_10to15p)
{
    double r = SHIKI_NO_KEISAN_Eval(L"roundup(1e15)");
    BOOST_CHECK(r == 1e15);
    r = SHIKI_NO_KEISAN_Eval(L"roundup(-1e15)");
    BOOST_CHECK(r == -1e15);
}

//------------------------------------------------------------
//
// round
//

BOOST_AUTO_TEST_CASE(test_round_posi_def)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"round(123.45)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 123);
}

BOOST_AUTO_TEST_CASE(test_round_posi_zero)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"round(123.45, 0)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 123);
}

BOOST_AUTO_TEST_CASE(test_round_one)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"round(123.45, 1)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, 123.5, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_round_posi_one)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"round(123.45, -1)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 120);
}

BOOST_AUTO_TEST_CASE(test_round_neg_posi_def)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"round(-123.45)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == -123);
}

BOOST_AUTO_TEST_CASE(test_round_neg_posi_zero)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"round(-123.45, 0)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == -123);
}

BOOST_AUTO_TEST_CASE(test_round_neg_one)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"round(-123.45, 1)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, -123.5, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_round_neg_posi_one)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"round(-123.45, -1)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == -120);
}

BOOST_AUTO_TEST_CASE(test_round_plus_two)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"round(123.45*(1+5e-16), 2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, 123.45, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_round_minus_two)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"round(123.45*(1-5e-16), 2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, 123.45, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_round_neg_plus_two)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"round(-123.45*(1+5e-16), 2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, -123.45, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_round_neg_minus_two)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"round(-123.45*(1-5e-16), 2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, -123.45, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_round_10to15p)
{
    double r = SHIKI_NO_KEISAN_Eval(L"round(1e15)");
    BOOST_CHECK(r == 1e15);
    r = SHIKI_NO_KEISAN_Eval(L"round(-1e15)");
    BOOST_CHECK(r == -1e15);
}

//------------------------------------------------------------

// $NOW$ round

// end of <test_round.cpp>
