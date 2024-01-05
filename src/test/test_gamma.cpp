// <test_gamma.cpp> -*- coding: utf-8 -*-
//
// Project shiki-no-keisan-dll
// Copyright (C) 2023 neige68
//
/// \file
/// \brief ガンマ関数のテスト
//
// Compiler: VC14.2
//

#define BOOST_TEST_MODULE TestGamma
#include <boost/test/unit_test.hpp>

#include "test.h"
#include "shiki_no_keisan.h"

#include <cmath>
#include <limits>

using namespace std;
using namespace std::string_literals;

//------------------------------------------------------------
//
// gamma
//

// Γ(1/2)=sqrt(pi)
BOOST_AUTO_TEST_CASE(test_gamma_half)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"gamma(1/2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, sqrt(M_PI), tolerance_percent);
}

// Γ(1)=0!=1
BOOST_AUTO_TEST_CASE(test_gamma_one)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"gamma(1)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 1);
}

// Γ(n+1)=nΓ(n)より
// Γ(1.5)=0.5Γ(0.5)=sqrt(pi)/2
BOOST_AUTO_TEST_CASE(test_gamma_one_half)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"gamma(3/2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, sqrt(M_PI) / 2, tolerance_percent);
}

// Γ(2)=1!=1
BOOST_AUTO_TEST_CASE(test_gamma_two)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"gamma(2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 1);
}

// Γ(n+1)=nΓ(n)より
// Γ(2.5)=1.5Γ(1.5)=1.5*0.5*Γ(0.5)=1.5*0.5*sqrt(pi)
BOOST_AUTO_TEST_CASE(test_gamma_two_half)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"gamma(5/2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, sqrt(M_PI) * 0.5 * 1.5, tolerance_percent);
}

// Γ(3)=2!=2
BOOST_AUTO_TEST_CASE(test_gamma_three)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"gamma(3)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 2);
}

// Γ(z)Γ(1-z)=π/(sin πz) (z is not integer) より
// Γ(1-z)=π/(sin πz * Γ(z))
// Γ(-0.5) は -0.5=1-z とおくと z=1.5 より
// Γ(-0.5)=π/(sin π*1.5 * Γ(1.5)) = π/(-1 * sqrt(π)/2) = -2π / sqrt(π) = -2 sqrt(π)
BOOST_AUTO_TEST_CASE(test_gamma_neg_half)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"gamma(-1/2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, -2 * sqrt(M_PI), tolerance_percent);
}

// Γ(1/2)=sqrt(pi)
BOOST_AUTO_TEST_CASE(test_gammaln_half)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"gammaln(1/2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, log(sqrt(M_PI)), tolerance_percent);
}

// Γ(1)=0!=1
BOOST_AUTO_TEST_CASE(test_gammaln_one)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"gammaln(1)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 0);
}

// Γ(n+1)=nΓ(n)より
// Γ(1.5)=0.5Γ(0.5)=sqrt(pi)/2
BOOST_AUTO_TEST_CASE(test_gammaln_one_half)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"gammaln(3/2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, log(sqrt(M_PI) / 2), tolerance_percent);
}

// Γ(2)=1!=1
BOOST_AUTO_TEST_CASE(test_gammaln_two)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"gammaln(2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK(r == 0);
}

// Γ(n+1)=nΓ(n)より
// Γ(2.5)=1.5Γ(1.5)=1.5*0.5*Γ(0.5)=1.5*0.5*sqrt(pi)
BOOST_AUTO_TEST_CASE(test_gammaln_two_half)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"gammaln(5/2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, log(sqrt(M_PI)) + log(0.5) + log(1.5), tolerance_percent);
}

// Γ(3)=2!=2
BOOST_AUTO_TEST_CASE(test_gammaln_three)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"gammaln(3)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, log(2), tolerance_percent);
}

// Γ(z)Γ(1-z)=π/(sin πz) (z is not integer) より
// Γ(1-z)=π/(sin πz * Γ(z))
// Γ(-0.5) は -0.5=1-z とおくと z=1.5 より
// Γ(-0.5)=π/(sin π*1.5 * Γ(1.5)) = π/(-1 * sqrt(π)/2) = -2π / sqrt(π) = -2 sqrt(π)
BOOST_AUTO_TEST_CASE(test_gammaln_neg_half)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    const double r = SHIKI_NO_KEISAN_Eval(L"gammaln(-1/2)");
    BOOST_CHECK(SHIKI_NO_KEISAN_GetErrorMessage() == L""s);
    BOOST_CHECK_CLOSE(r, log(2 * sqrt(M_PI)), tolerance_percent);
}

//------------------------------------------------------------

// end of <test_gamma.cpp>
