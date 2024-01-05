// <sample.cs>
// 
// Project shiki-no-keisan-dll/sample/cs

// Copyright (C) 2024 neige68
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  https://www.boost.org/LICENSE_1_0.txt)

// Note: sample
// 
// Compiler: Visual Studio 2019 以降の CSC
// 
using System;
using System.Runtime.InteropServices; // DLL Import
static class cssample
{
    //------------------------------------------------------------
    // 計算式文字列を受け取って評価して返す
    // SHIKI_NO_KEISAN_Eval
    //------------------------------------------------------------
    // SHIKI_NO_KEISAN_SPEC double __stdcall SHIKI_NO_KEISAN_Eval(const wchar_t* mathExpr);
    //
    [DllImport("x86/neige68.ShikiNoKeisan.dll", EntryPoint="SHIKI_NO_KEISAN_Eval", CharSet = CharSet.Unicode)]
    public static extern double X86_SHIKI_NO_KEISAN_Eval(string mathExpr);
    //
    [DllImport("x64/neige68.ShikiNoKeisan.dll", EntryPoint="SHIKI_NO_KEISAN_Eval", CharSet = CharSet.Unicode)]
    public static extern double X64_SHIKI_NO_KEISAN_Eval(string mathExpr);
    //
    // 仲介関数
    public static double SHIKI_NO_KEISAN_Eval(string mathExpr)
    {
        double Result;
        if (IntPtr.Size == 4)
            Result = X86_SHIKI_NO_KEISAN_Eval(mathExpr);
        else if (IntPtr.Size == 8)
            Result = X64_SHIKI_NO_KEISAN_Eval(mathExpr);
        else
            throw new Exception("Unexpected Pointer Size.");
        return Result;
    }
    //------------------------------------------------------------
    // エラーメッセージ
    // SHIKI_NO_KEISAN_GetErrorMessage
    //------------------------------------------------------------
    // SHIKI_NO_KEISAN_SPEC const wchar_t* __stdcall SHIKI_NO_KEISAN_GetErrorMessage();
    //
    [DllImport("x86/neige68.ShikiNoKeisan.dll", EntryPoint="SHIKI_NO_KEISAN_GetErrorMessage")]
    public static extern IntPtr X86_SHIKI_NO_KEISAN_GetErrorMessage();
    [DllImport("x64/neige68.ShikiNoKeisan.dll", EntryPoint="SHIKI_NO_KEISAN_GetErrorMessage")]
    public static extern IntPtr X64_SHIKI_NO_KEISAN_GetErrorMessage();
    //
    // 仲介関数
    public static string SHIKI_NO_KEISAN_GetErrorMessage()
    {
        IntPtr pstr;
        if (IntPtr.Size == 4)
            pstr = X86_SHIKI_NO_KEISAN_GetErrorMessage();
        else if (IntPtr.Size == 8)
            pstr = X64_SHIKI_NO_KEISAN_GetErrorMessage();
        else
            throw new System.Exception("Unexpected Pointer Size.");
        return System.Runtime.InteropServices.Marshal.PtrToStringAuto(pstr); // CS の string に変換
    }
    //------------------------------------------------------------
    // エラーメッセージをクリア
    // SHIKI_NO_KEISAN_ClearErrorMessage
    //------------------------------------------------------------
    // SHIKI_NO_KEISAN_SPEC void __stdcall SHIKI_NO_KEISAN_ClearErrorMessage();
    //
    [DllImport("x86/neige68.ShikiNoKeisan.dll", EntryPoint="SHIKI_NO_KEISAN_ClearErrorMessage")]
    public static extern void X86_SHIKI_NO_KEISAN_ClearErrorMessage();
    [DllImport("x64/neige68.ShikiNoKeisan.dll", EntryPoint="SHIKI_NO_KEISAN_ClearErrorMessage")]
    public static extern void X64_SHIKI_NO_KEISAN_ClearErrorMessage();
    //
    // 仲介関数
    public static void SHIKI_NO_KEISAN_ClearErrorMessage()
    {
        if (IntPtr.Size == 4)
            X86_SHIKI_NO_KEISAN_ClearErrorMessage();
        else if (IntPtr.Size == 8)
            X64_SHIKI_NO_KEISAN_ClearErrorMessage();
        else
            throw new System.Exception("Unexpected Pointer Size.");
    }
    //============================================================
    // 評価して表示
    static void EvalPrint(string Expr)
    {
        SHIKI_NO_KEISAN_ClearErrorMessage();
        double Result = SHIKI_NO_KEISAN_Eval(Expr);
        if (double.IsNaN(Result)) {
            string Msg = SHIKI_NO_KEISAN_GetErrorMessage();
            if (!string.IsNullOrEmpty(Msg)) {
                Console.WriteLine("ERROR: " + Expr + " : " + Msg);
                return;
            }
        }
        Console.WriteLine(Expr + " = " + Result);
    }
    //============================================================
    // メイン
    //============================================================
    static void Main()
    {
        Console.Write("sample.cs");
        if (IntPtr.Size == 4)
            Console.Write(" x86");
        else if (IntPtr.Size == 8)
            Console.Write(" x64");
        else
            Console.Write(" Unknown");
        Console.WriteLine("");
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
}
// end of <sample.cs>
