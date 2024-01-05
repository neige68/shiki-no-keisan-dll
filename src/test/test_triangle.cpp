// <test_triangle.cpp.cpp> -*- coding: utf-8 -*-
//
// Project shiki-no-keisan-dll
// Copyright (C) 2024 neige68
//
/// \file
/// \brief 三角関数のテスト
//
// Compiler: VC14.2
//

#define BOOST_TEST_MODULE TestTriangle
#include <boost/test/unit_test.hpp>

#include "test.h"
#include "shiki_no_keisan.h"

#include <cmath>
#include <limits>

using namespace std;
using namespace std::string_literals;

//------------------------------------------------------------
//
// sin
//

BOOST_AUTO_TEST_CASE(test_sin_zero)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"sin(0)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 0);
}

BOOST_AUTO_TEST_CASE(test_sin_one_sixth_pi)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"sin(3.1415926535897932/6)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, 0.5, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_sin_one_third_pi)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"sin(3.1415926535897932/3)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, sqrt(3) / 2, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_sin_half_pi)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"sin(3.1415926535897932/2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, 1, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_sin_pi)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"sin(3.1415926535897932)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_SMALL(r, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_sin_2pi)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"sin(3.1415926535897932*2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_SMALL(r, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_sin_neg_one_sixth_pi)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"sin(-3.1415926535897932/6)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, -0.5, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_sin_inf)
{
    const double r = SHIKI_NO_KEISAN_Eval(L"sin(inf)");
    BOOST_CHECK(isnan(r));
}

//------------------------------------------------------------
//
// cos
//

BOOST_AUTO_TEST_CASE(test_cos_zero)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"cos(0)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 1);
}

BOOST_AUTO_TEST_CASE(test_cos_one_sixth_pi)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"cos(3.1415926535897932/6)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, sqrt(3) / 2, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_cos_one_third_pi)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"cos(3.1415926535897932/3)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, 0.5, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_cos_half_pi)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"cos(3.1415926535897932/2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_SMALL(r, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_cos_pi)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"cos(3.1415926535897932)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, -1, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_cos_2pi)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"cos(3.1415926535897932*2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, 1, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_cos_neg_one_sixth_pi)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"cos(-3.1415926535897932/6)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, sqrt(3) / 2, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_cos_inf)
{
    const double r = SHIKI_NO_KEISAN_Eval(L"cos(inf)");
    BOOST_CHECK(isnan(r));
}

//------------------------------------------------------------
//
// tan
//

BOOST_AUTO_TEST_CASE(test_tan_zero)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"tan(0)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 0);
}

BOOST_AUTO_TEST_CASE(test_tan_one_sixth_pi)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"tan(3.1415926535897932/6)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, 1 / sqrt(3), tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_tan_one_third_pi)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"tan(3.1415926535897932/3)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, sqrt(3), tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_tan_half_pi)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"tan(3.1415926535897932/2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r > 1 / epsilon);
}

BOOST_AUTO_TEST_CASE(test_tan_pi)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"tan(3.1415926535897932)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_SMALL(r, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_tan_2pi)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"tan(3.1415926535897932*2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_SMALL(r, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_tan_neg_one_sixth_pi)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"tan(-3.1415926535897932/6)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, -1 / sqrt(3), tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_tan_inf)
{
    const double r = SHIKI_NO_KEISAN_Eval(L"tan(inf)");
    BOOST_CHECK(isnan(r));
}

//------------------------------------------------------------
//
// asin
//

BOOST_AUTO_TEST_CASE(test_asin_sin_zero)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"asin(sin(0))");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 0);
}

BOOST_AUTO_TEST_CASE(test_asin_sin_one_sixth_pi)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"asin(sin(3.1415926535897932/6))");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, M_PI / 6, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_asin_sin_one_third_pi)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"asin(sin(3.1415926535897932/3))");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, M_PI / 3, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_asin_sin_half_pi)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"asin(sin(3.1415926535897932/2))");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, M_PI / 2, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_asin_sin_neg_one_sixth_pi)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"asin(sin(-3.1415926535897932/6))");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, -M_PI / 6, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_asin_two)
{
    const double r = SHIKI_NO_KEISAN_Eval(L"asin(2)");
    BOOST_CHECK(isnan(r));
}

BOOST_AUTO_TEST_CASE(test_asin_inf)
{
    const double r = SHIKI_NO_KEISAN_Eval(L"asin(inf)");
    BOOST_CHECK(isnan(r));
}

//------------------------------------------------------------
//
// acos
//

BOOST_AUTO_TEST_CASE(test_acos_cos_zero)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"acos(cos(0))");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_SMALL(r, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_acos_cos_one_sixth_pi)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"acos(cos(3.1415926535897932/6))");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, M_PI / 6, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_acos_cos_one_third_pi)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"acos(cos(3.1415926535897932/3))");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, M_PI / 3, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_acos_zero)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"acos(0)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, M_PI / 2, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_acos_neg_one)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"acos(-1)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, M_PI, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_acos_two)
{
    const double r = SHIKI_NO_KEISAN_Eval(L"acos(2)");
    BOOST_CHECK(isnan(r));
}

BOOST_AUTO_TEST_CASE(test_acos_inf)
{
    const double r = SHIKI_NO_KEISAN_Eval(L"acos(inf)");
    BOOST_CHECK(isnan(r));
}

//------------------------------------------------------------
//
// atan
//

BOOST_AUTO_TEST_CASE(test_atan_zero)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"atan(0)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 0);
}

BOOST_AUTO_TEST_CASE(test_atan_one)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"atan(1)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, M_PI / 4, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_atan_neg_one)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"atan(-1)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, -M_PI / 4, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_atan_tan_one_sixth_pi)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"atan(tan(3.1415926535897932/6))");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, M_PI / 6, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_atan_tan_one_third_pi)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"atan(tan(3.1415926535897932/3))");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, M_PI / 3, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_atan_tan_half_pi)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"atan(tan(3.1415926535897932/2))");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, M_PI / 2, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_atan_tan_neg_one_sixth_pi)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"atan(tan(-3.1415926535897932/6))");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, -M_PI / 6, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_atan_inf)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"atan(inf)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, M_PI / 2, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_atan_neg_inf)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"atan(-inf)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, -M_PI / 2, tolerance_percent);
}

//------------------------------------------------------------
//
// atan2
//

BOOST_AUTO_TEST_CASE(test_atan2_one_sqrt3)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"atan2(1,sqrt(3))");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, M_PI / 6, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_atan2_one_one)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"atan2(1,1)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, M_PI / 4, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_atan2_sqrt3_one)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"atan2(sqrt(3),1)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, M_PI / 3, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_atan2_one_zero)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"atan2(1,0)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, M_PI / 2, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_atan2_sqrt3_neg_one)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"atan2(sqrt(3),-1)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, 2 * M_PI / 3, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_atan2_one_neg_one)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"atan2(1,-1)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, 3 * M_PI / 4, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_atan2_one_neg_sqrt3)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"atan2(1,-sqrt(3))");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, 5 * M_PI / 6, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_atan2_zero_neg_one)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"atan2(0,-1)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, M_PI, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_atan2_neg_one_sqrt3)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"atan2(-1,sqrt(3))");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, -M_PI / 6, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_atan2_neg_one_one)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"atan2(-1,1)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, -M_PI / 4, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_atan2_neg_sqrt3_one)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"atan2(-sqrt(3),1)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, -M_PI / 3, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_atan2_neg_one_zero)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"atan2(-1,0)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, -M_PI / 2, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_atan2_neg_sqrt3_neg_one)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"atan2(-sqrt(3),-1)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, -2 * M_PI / 3, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_atan2_neg_one_neg_one)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"atan2(-1,-1)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, -3 * M_PI / 4, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_atan2_neg_one_neg_sqrt3)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"atan2(-1,-sqrt(3))");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, -5 * M_PI / 6, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_atan2_zero_inf)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"atan2(0,inf)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_SMALL(r, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_atan2_inf_zero)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"atan2(inf,0)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, M_PI / 2, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_atan2_zero_neg_inf)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"atan2(0,-inf)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, M_PI, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_atan2_neg_inf_zero)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"atan2(-inf,0)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, -M_PI / 2, tolerance_percent);
}

//------------------------------------------------------------

// end of <test_triangle.cpp>
