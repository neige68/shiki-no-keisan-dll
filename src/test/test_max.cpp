// <test_max.cpp> -*- coding: utf-8 -*-
//
// Project shiki-no-keisan-dll
// Copyright (C) 2024 neige68
//
/// \file
/// \brief max, min のテスト
//
// Compiler: VC14.2
//

#define BOOST_TEST_MODULE TestMax
#include <boost/test/unit_test.hpp>

#include "test.h"
#include "shiki_no_keisan.h"

#include <cmath>
#include <limits>

using namespace std;
using namespace std::string_literals;

//------------------------------------------------------------
//
// max
//

BOOST_AUTO_TEST_CASE(test_max_increase)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"max(1, 2, 3)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 3);
}

BOOST_AUTO_TEST_CASE(test_max_increase_with_nan)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"max(1, nan, 3)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 3);
}

BOOST_AUTO_TEST_CASE(test_max_increase_nan_starts)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"max(nan, 2, 3)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 3);
}

BOOST_AUTO_TEST_CASE(test_max_decrease)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"max(4, 3, 2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 4);
}

BOOST_AUTO_TEST_CASE(test_max_convex_upward)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"max(-4, 0, -3)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 0);
}

BOOST_AUTO_TEST_CASE(test_max_convex_downward)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"max(-4, -8, -3)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == -3);
}

BOOST_AUTO_TEST_CASE(test_max_increase_to_inf)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"max(1, 2, inf)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == numeric_limits<double>::infinity());
}

BOOST_AUTO_TEST_CASE(test_max_decrease_from_inf)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"max(inf, 3, -1)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == numeric_limits<double>::infinity());
}

BOOST_AUTO_TEST_CASE(test_max_increase_from_neg_inf)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"max(-inf, -1, 3)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 3);
}

//------------------------------------------------------------
//
// max
//

BOOST_AUTO_TEST_CASE(test_min_increase)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"min(1, 2, 3)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 1);
}

BOOST_AUTO_TEST_CASE(test_min_increase_with_nan)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"min(1, nan, 3)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 1);
}

BOOST_AUTO_TEST_CASE(test_min_decrease)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"min(4, 3, 2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 2);
}

BOOST_AUTO_TEST_CASE(test_min_decrease_nan_starts)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"min(nan, 2, 1)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 1);
}

BOOST_AUTO_TEST_CASE(test_min_convex_upward)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"min(-4, 0, -3)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == -4);
}

BOOST_AUTO_TEST_CASE(test_min_convex_downward)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"min(-4, -8, -3)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == -8);
}

BOOST_AUTO_TEST_CASE(test_min_increase_to_inf)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"min(1, 2, inf)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 1);
}

BOOST_AUTO_TEST_CASE(test_min_decrease_from_inf)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"min(inf, 3, -1)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == -1);
}

BOOST_AUTO_TEST_CASE(test_min_increase_from_neg_inf)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"min(-inf, -1, 3)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == -numeric_limits<double>::infinity());
}

//------------------------------------------------------------

// end of <test_max.cpp>
