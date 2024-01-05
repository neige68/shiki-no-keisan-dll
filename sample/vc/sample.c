// <sample.c> -*- coding: utf-8 -*-
//
// Project shiki-no-keisan-dll/sample/vc
// Copyright (C) 2024 neige68
//
/// \file
/// \brief サンプルプログラム
//
// Compiler: VC14.2
//

#include "shiki_no_keisan.h"

#include <math.h>               // isnan
#include <stdio.h>              // printf

void EvalPrint(const char* str)
{
    double result;
    const char* msg;
    
    SHIKI_NO_KEISAN_ClearErrorMessage();
    result = SHIKI_NO_KEISAN_EvalA(str);
    if (isnan(result)) {
        msg = SHIKI_NO_KEISAN_GetErrorMessageA();
        if (msg && *msg) {
            printf("Error: %s : %s\n", str, msg);
            return;
        }
    }
    printf("%s = %g\n", str, result);
}

int main()
{
    printf("sample.c");
#if defined(_WIN64)
    printf(" x64");
#else        
    printf(" x86");
#endif
#if defined(NDEBUG)
    printf(" Release");
#else
    printf(" Debug");
#endif
    printf(" Version\n");
    //
    EvalPrint("2*2+2/2");
    EvalPrint("1/3");
    EvalPrint("1/3-0.3333333333333");
    EvalPrint("1/0");
    EvalPrint("(-1)/0");
    EvalPrint("0/0");
    EvalPrint("0/0+");
    EvalPrint("0/0+Hoge");
    EvalPrint("2**3**4");
    EvalPrint("2**(3**4)");
    EvalPrint("(2**3)**4");
    EvalPrint("2^(1/2)");
    EvalPrint("-2^(1/2)");
    EvalPrint("-2^-(1/2)");
    EvalPrint("(-2)^-(1/2)");
    EvalPrint("(2^(1/12))^7");
    EvalPrint("gamma(0.5)**2");
    EvalPrint("exp(-1/0)");
    EvalPrint("round(exp(gammaln(0.5)*2),2)");
}

// end of <sample.c>
