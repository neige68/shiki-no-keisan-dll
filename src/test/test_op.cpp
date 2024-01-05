// <test_op.cpp> -*- coding: utf-8 -*-
//
// Project shiki-no-keisan-dll
// Copyright (C) 2024 neige68
//
/// \file
/// \brief 演算子のテスト
//
// Compiler: VC14.2
//

#define BOOST_TEST_MODULE TestOp
#include <boost/test/unit_test.hpp>

#include "test.h"
#include "shiki_no_keisan.h"

#include <cmath>
#include <limits>

using namespace std;
using namespace std::string_literals;

//------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_add)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"2+3+4");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, 2+3+4, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_difference)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"2-3-4");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, 2-3-4, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_difference_and_paren)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"2-(3-4)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, 2-(3-4), tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_multiple)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"2*3*4");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, 2*3*4, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_divide)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"2/3/4");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, 2.0/3/4, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_divide_by_zero)
{
    BOOST_CHECK(std::numeric_limits<double>::has_infinity);
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"2/0");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == std::numeric_limits<double>::infinity());
}

BOOST_AUTO_TEST_CASE(test_divide_by_inf)
{
    BOOST_CHECK(std::numeric_limits<double>::has_infinity);
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"2/(2/0)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 0);
}

BOOST_AUTO_TEST_CASE(test_divide_negative_by_zero)
{
    BOOST_CHECK(std::numeric_limits<double>::has_infinity);
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"-2/0");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == -std::numeric_limits<double>::infinity());
}

BOOST_AUTO_TEST_CASE(test_divide_zero_by_zero)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"0/0");
    BOOST_CHECK(isnan(r));
}

BOOST_AUTO_TEST_CASE(test_nan_plus_zero)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"0/0+0");
    BOOST_CHECK(isnan(r));
}

BOOST_AUTO_TEST_CASE(test_divide_and_paren)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"2/(3/4)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, 2/(3/4.0), tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_uniplus)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"+2/+3/+4");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, +2.0/+3/+4, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_uniminus)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"-2/-3/-4");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, -2.0/-3/-4, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_exponent)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"2^3^4");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, pow(2, pow(3, 4)), tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_exponent_double_aster)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"2**3**4");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, 2417851639229258349412352.0, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_exponent_and_paren)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"(2^3)^4");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, pow(pow(2, 3), 4), tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_exponent_double_aster_and_paren)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"(2**3)**4");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, pow(pow(2, 3), 4), tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_admdp)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"2^3-(4*5+6/7)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, -90/7.0, tolerance_percent);
}

//------------------------------------------------------------

// end of <test_op.cpp>
