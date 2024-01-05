' <sample.vb>
'
' Project shiki-no-keisan-dll/sample/vb

' Copyright (C) 2024 neige68
' Distributed under the Boost Software License, Version 1.0.
' (See accompanying file LICENSE or copy at
'  https://www.boost.org/LICENSE_1_0.txt)

' Note: sample
' 
' Compiler: Visual Studio 2019 以降の VBC
'
Module vbsample
    '------------------------------------------------------------
    ' 計算式文字列を受け取って評価して返す
    ' SHIKI_NO_KEISAN_Eval
    '------------------------------------------------------------
    ' SHIKI_NO_KEISAN_SPEC double __stdcall SHIKI_NO_KEISAN_Eval(const wchar_t* mathExpr);
    Declare Unicode Function X86_SHIKI_NO_KEISAN_Eval Lib "x86\neige68.ShikiNoKeisan.dll" Alias "SHIKI_NO_KEISAN_Eval" (mathExpr As String) As Double
    Declare Unicode Function X64_SHIKI_NO_KEISAN_Eval Lib "x64\neige68.ShikiNoKeisan.dll" Alias "SHIKI_NO_KEISAN_Eval" (mathExpr As String) As Double
    ' 仲介関数
    Function SHIKI_NO_KEISAN_Eval (mathExpr As String) As Double
        Dim Result As Double
        If IntPtr.Size = 4 Then
            Result = X86_SHIKI_NO_KEISAN_Eval(mathExpr)
        Else If IntPtr.Size = 8 Then
            Result = X64_SHIKI_NO_KEISAN_Eval(mathExpr)
        Else
            Throw New System.Exception("Unexpected Pointer Size.")
        End If
        Return Result
    End Function
    '------------------------------------------------------------
    ' エラーメッセージ
    ' SHIKI_NO_KEISAN_GetErrorMessage
    '------------------------------------------------------------
    ' SHIKI_NO_KEISAN_SPEC const wchar_t* __stdcall SHIKI_NO_KEISAN_GetErrorMessage();
    Declare Unicode Function X86_SHIKI_NO_KEISAN_GetErrorMessage Lib "x86\neige68.ShikiNoKeisan.dll" Alias "SHIKI_NO_KEISAN_GetErrorMessage" As IntPtr
    Declare Unicode Function X64_SHIKI_NO_KEISAN_GetErrorMessage Lib "x64\neige68.ShikiNoKeisan.dll" Alias "SHIKI_NO_KEISAN_GetErrorMessage" As IntPtr
    ' 仲介関数
    Function SHIKI_NO_KEISAN_GetErrorMessage As String
        Dim pstr As IntPtr
        If IntPtr.Size = 4 Then
            pstr = X86_SHIKI_NO_KEISAN_GetErrorMessage
        Else If IntPtr.Size = 8 Then
            pstr = X64_SHIKI_NO_KEISAN_GetErrorMessage
        Else
            Throw New System.Exception("Unexpected Pointer Size.")
        End If
        Return Runtime.InteropServices.Marshal.PtrToStringAuto(pstr) ' VB の String に変換
    End Function
    '------------------------------------------------------------
    ' エラーメッセージをクリア
    ' SHIKI_NO_KEISAN_ClearErrorMessage
    '------------------------------------------------------------
    ' SHIKI_NO_KEISAN_SPEC void __stdcall SHIKI_NO_KEISAN_ClearErrorMessage();
    Declare Unicode Sub X86_SHIKI_NO_KEISAN_ClearErrorMessage Lib "x86\neige68.ShikiNoKeisan.dll" Alias "SHIKI_NO_KEISAN_ClearErrorMessage" 
    Declare Unicode Sub X64_SHIKI_NO_KEISAN_ClearErrorMessage Lib "x64\neige68.ShikiNoKeisan.dll" Alias "SHIKI_NO_KEISAN_ClearErrorMessage" 
    ' 仲介関数
    Sub SHIKI_NO_KEISAN_ClearErrorMessage
        If IntPtr.Size = 4 Then
            X86_SHIKI_NO_KEISAN_ClearErrorMessage
        Else If IntPtr.Size = 8 Then
            X64_SHIKI_NO_KEISAN_ClearErrorMessage
        Else
            Throw New System.Exception("Unexpected Pointer Size.")
        End If
    End Sub
    '============================================================
    ' 評価して表示
    Sub EvalPrint(Expr As String)
        SHIKI_NO_KEISAN_ClearErrorMessage
        Dim Result As Double = SHIKI_NO_KEISAN_Eval(Expr)
        If Double.IsNaN(Result) Then
            Dim Msg As String = SHIKI_NO_KEISAN_GetErrorMessage
            If Msg > "" Then
                Console.WriteLine("ERROR: " & Expr & " : " & Msg)
                Exit Sub
            End If
        End If
        Console.WriteLine(Expr & " = " & Result)
    End Sub
    '============================================================
    ' メイン
    '============================================================
    Sub Main
        EvalPrint("2*2+2/2")
        EvalPrint("1/3")
        EvalPrint("1/3-0.3333333333333")
        EvalPrint("1/0")
        EvalPrint("(-1)/0")
        EvalPrint("0/0")
        EvalPrint("0/0+")
        EvalPrint("0/0+Hoge")
        EvalPrint("2**3**4")
        EvalPrint("2**(3**4)")
        EvalPrint("(2**3)**4")
        EvalPrint("2^(1/2)")
        EvalPrint("-2^(1/2)")
        EvalPrint("-2^-(1/2)")
        EvalPrint("(-2)^-(1/2)")
        EvalPrint("(2^(1/12))^7")
        EvalPrint("gamma(0.5)**2")
        EvalPrint("exp(-1/0)")
        EvalPrint("round(exp(gammaln(0.5)*2),2)")
    End Sub
End Module
' end of <sample.vb>
