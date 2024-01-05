// <test_rand.cpp> -*- coding: utf-8 -*-
//
// Project shiki-no-keisan-dll
// Copyright (C) 2024 neige68
//
/// \file
/// \brief 乱数のテスト
//
// Compiler: VC14.2
//

#define BOOST_TEST_MODULE TestRand
#include <boost/test/unit_test.hpp>

#include "test.h"
#include "shiki_no_keisan.h"

#include <cmath>
#include <limits>

using namespace std;
using namespace std::string_literals;

//------------------------------------------------------------
//
// random
//

BOOST_AUTO_TEST_CASE(test_random_zero)
{
    for (int i = 0; i < 100; i++) {
        SHIKI_NO_KEISAN_ClearErrorMessage();
        const double r = SHIKI_NO_KEISAN_Eval(L"random(0)");
        BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
        BOOST_CHECK(0 <= r && r < 1);
    }
}

BOOST_AUTO_TEST_CASE(test_random_six)
{
    for (int i = 0; i < 100; i++) {
        SHIKI_NO_KEISAN_ClearErrorMessage();
        const double r = SHIKI_NO_KEISAN_Eval(L"random(6)");
        BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
        BOOST_CHECK(0 <= r && r < 6);
        BOOST_CHECK(fabs(fmod(r, 1)) <= numeric_limits<double>::epsilon() * 6);
    }
}

BOOST_AUTO_TEST_CASE(test_random_six_plus)
{
    for (int i = 0; i < 100; i++) {
        SHIKI_NO_KEISAN_ClearErrorMessage();
        const double r = SHIKI_NO_KEISAN_Eval(L"random(6+7e-15)");
        BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
        BOOST_CHECK(0 <= r && r < 6+7e-15);
    }
}

//------------------------------------------------------------

// end of <test_rand.cpp>
