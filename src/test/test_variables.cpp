// <test_variables.cpp.cpp> -*- coding: utf-8 -*-
//
// Project shiki-no-keisan-dll

// Copyright (C) 2024 neige68
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  https://www.boost.org/LICENSE_1_0.txt)

/// \file
/// \brief 変数のテスト
//
// Compiler: VC14.2
//

#define BOOST_TEST_MODULE TestVariables
#include <boost/test/unit_test.hpp>

#include "test.h"
#include "shiki_no_keisan.h"

#include <thread>

using namespace std;
using namespace std::string_literals;

//------------------------------------------------------------
//
// variables
//

BOOST_AUTO_TEST_CASE(test_variables)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"A=2+3;B=3+5;1+A*B");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 41);
}

BOOST_AUTO_TEST_CASE(test_variables_undef)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"A=2+3;B=3+5;1+D*B");
    BOOST_CHECK(isnan(r));
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() != L""s);
    wcout << SHIKI_NO_KEISAN_GetErrorMessage() << endl;
}

BOOST_AUTO_TEST_CASE(test_variables_kanji)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"往路=120;復路=80;2/(1/往路+1/復路)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, 96, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_variables_hiragana)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"おうろ=120;ふくろ=80;2/(1/おうろ+1/ふくろ)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, 96, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_variables_halfwidthkatakana)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"ｵｳﾛ=120;ﾌｸﾛ=80;2/(1/ｵｳﾛ+1/ﾌｸﾛ)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, 96, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_variables_hangul)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"왕로=120;복로=80;2/(1/왕로+1/복로)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, 96, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_variables_deutsch)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"Hinfahrt=120;Rückfahrt=80;2/(1/Hinfahrt+1/Rückfahrt)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, 96, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_variables_russian)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"путь_туда=120;путь_обратно=80;2/(1/путь_туда+1/путь_обратно)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, 96, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_variables_count)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    SHIKI_NO_KEISAN_Eval(L"COUNT=0");
    const int n = 100;
    for (int i = 0; i < n; i++)
        SHIKI_NO_KEISAN_Eval(L"COUNT=COUNT+1");
    const double r = SHIKI_NO_KEISAN_Eval(L"COUNT");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, n, tolerance_percent);
}

BOOST_AUTO_TEST_CASE(test_variables_count_multithread)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    SHIKI_NO_KEISAN_Eval(L"COUNT=0");
    const int n = 1000;
    unique_ptr<thread> ths[n];
    for (int i = 0; i < n; i++)
        ths[i].reset(new thread{[] {SHIKI_NO_KEISAN_Eval(L"COUNT=COUNT+1");}});
    for (int i = 0; i < n; i++)
        ths[i]->join();
    const double r = SHIKI_NO_KEISAN_Eval(L"COUNT");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, n, tolerance_percent);
}

//------------------------------------------------------------

// end of <test_variables.cpp>
