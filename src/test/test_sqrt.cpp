// <test_sqrt.cpp> -*- coding: utf-8 -*-
//
// Project shiki-no-keisan-dll
// Copyright (C) 2024 neige68
//
/// \file
/// \brief sqrt のテスト
//
// Compiler: VC14.2
//

#define BOOST_TEST_MODULE TestSqrt
#include <boost/test/unit_test.hpp>

#include "test.h"
#include "shiki_no_keisan.h"

#include <cmath>
#include <limits>

using namespace std;
using namespace std::string_literals;

//------------------------------------------------------------
//
// sqrt
//

BOOST_AUTO_TEST_CASE(test_sqrt2)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"sqrt(2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, sqrt(2), tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_sqrt4)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"sqrt(4)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 2);
}

BOOST_AUTO_TEST_CASE(test_sqrt_0)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"sqrt(0)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 0);
}

BOOST_AUTO_TEST_CASE(test_sqrt_inf)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"sqrt(inf)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == numeric_limits<double>::infinity());
}

BOOST_AUTO_TEST_CASE(test_sqrt_neg)
{
    const double r = SHIKI_NO_KEISAN_Eval(L"sqrt(-2)");
    BOOST_CHECK(isnan(r));
}

//------------------------------------------------------------

// end of <test_sqrt.cpp>
