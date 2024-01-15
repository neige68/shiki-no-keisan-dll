// <shiki_no_keisan.h> -*- coding: utf-8 -*-
//
// Project shiki-no-keisan-dll

// Copyright (C) 2024 neige68
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  https://www.boost.org/LICENSE_1_0.txt)

/// \file
/// \brief 計算式評価 DLL
//
// Compiler: VC14.2
//

#ifndef shiki_no_keisan_h
#define shiki_no_keisan_h

#ifndef __cplusplus
#include <wchar.h>              // wchar_t
#endif

//
/// \def SHIKI_NO_KEISAN_SPEC
//
/// \brief DLL インポート/エクスポート指定
//
/// \details
/// DLL 作成時には __declspec(dllexport),
/// それ以外では __declspec(dllimport) と定義されることにより、
/// 関数などのエクスポートとインポートを行う。
//
#ifdef SHIKI_NO_KEISAN_EXPORT // DLL 作成側
# define SHIKI_NO_KEISAN_SPEC __declspec(dllexport)
#else
# define SHIKI_NO_KEISAN_SPEC __declspec(dllimport)
#endif

//============================================================

#ifdef __cplusplus
extern "C" {
#endif

//------------------------------------------------------------
//
/// 計算式文字列を受け取って評価して返す
//
/// エラー時は NaN が返される。 \n
/// C/C++ では isnan マクロ/インラインテンプレート関数で判定できる。 \n
/// VB.NET, C# では Double.IsNaN メソッドで判定できる。 \n
/// NaN が返された場合でも、エラーメッセージは空の場合がある。
SHIKI_NO_KEISAN_SPEC double __stdcall SHIKI_NO_KEISAN_Eval(const wchar_t* mathExpr);
/// 計算式文字列を受け取って評価して返す ANSI(MBCS) 版
SHIKI_NO_KEISAN_SPEC double __stdcall SHIKI_NO_KEISAN_EvalA(const char* mathExpr);

//------------------------------------------------------------
//
/// エラーメッセージをクリア
//
SHIKI_NO_KEISAN_SPEC void __stdcall SHIKI_NO_KEISAN_ClearErrorMessage();

//------------------------------------------------------------
//
/// エラーメッセージへの参照を返す
//
/// 静的なバッファ上のエラーメッセージのポインタを返す。 \n
/// 空文字列のこともある。 \n
/// VB.NET, C# では IntPtr で受け取り、
/// Runtime.InteropServices.Marshal.PtrToStringAuto で String に変換する。
SHIKI_NO_KEISAN_SPEC const wchar_t* __stdcall SHIKI_NO_KEISAN_GetErrorMessage();

/// エラーメッセージへの参照を返す ANSI(MBCS) 版
SHIKI_NO_KEISAN_SPEC const char* __stdcall SHIKI_NO_KEISAN_GetErrorMessageA();

//------------------------------------------------------------
//
/// 吸収相対誤差設定
//
/// 0 付近以外で吸収される誤差を設定します
//
/// \result 設定前の値
SHIKI_NO_KEISAN_SPEC double __stdcall SHIKI_NO_KEISAN_SetRelativeErrorThreshold(double e);

/// 吸収相対誤差取得
//
/// 0 付近以外で吸収される誤差を取得します
//
SHIKI_NO_KEISAN_SPEC double __stdcall SHIKI_NO_KEISAN_GetRelativeErrorThreshold();

//------------------------------------------------------------
//
/// 吸収絶対誤差設定
//
/// 0 付近で吸収される誤差を設定します
//
/// \result 設定前の値
SHIKI_NO_KEISAN_SPEC double __stdcall SHIKI_NO_KEISAN_SetAbsoluteErrorThreshold(double e);

/// 吸収絶対誤差取得
//
/// 0 付近で吸収される誤差を取得します
//
SHIKI_NO_KEISAN_SPEC double __stdcall SHIKI_NO_KEISAN_GetAbsoluteErrorThreshold();

//------------------------------------------------------------

/// 識別用メッセージ(ANSI)
SHIKI_NO_KEISAN_SPEC const char* __stdcall SHIKI_NO_KEISAN_GetIdentMessageA();

//------------------------------------------------------------

#ifdef __cplusplus
} // extern
#endif

//============================================================

#endif // shiki_no_keisan_h

// end of <shiki_no_keisan.h>
