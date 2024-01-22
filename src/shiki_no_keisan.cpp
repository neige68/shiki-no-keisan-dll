// <shiki_no_keisan.cpp> -*- coding: utf-8 -*-
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

#define SHIKI_NO_KEISAN_EXPORT
#include "shiki_no_keisan.h"

#include "bltinfun.h"           // BuiltInFunctions
#include "charconv.h"           // to_utf8

#include <boost/fusion/include/adapt_struct.hpp> // BOOST_FUSION_ADAPT_STRUCT
#include <boost/optional.hpp>                    // boost::optional
#include <boost/spirit/home/x3.hpp>              // boost::spirit::x3
#include <boost/spirit/home/x3/support/ast/variant.hpp> // boost::spirit::x3::variant

#include <cmath>                // std::fabs
#include <list>                 // std::list
#include <map>                  // std::map
#include <numeric>              // std::accumulate
#include <stdexcept>            // std::runtime_error
#include <string>               // std::string

using namespace std;

//************************************************************
// this part is based on spirit/example/x3/calc/calc4b.cpp
// Copyright (c) 2001-2014 Joel de Guzman

namespace x3 = boost::spirit::x3;

//------------------------------------------------------------
//
/// AST - 抽象構文木(Abstract Syntax Tree)
//

namespace ast {

/// 空
struct nil {};

struct signed_;
struct exp_operation;
struct expression;
struct function_call;
struct symbol;

/// オペランド(演算対象)
struct operand : x3::variant<
    nil
    , double
    , x3::forward_ast<signed_>
    , x3::forward_ast<exp_operation>
    , x3::forward_ast<expression>
    , x3::forward_ast<function_call>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};

/// 符号付け(単項演算)
struct signed_
{
    wchar_t sign;
    operand operand_;
};

/// 2項演算
struct operation
{
    wchar_t operator_;
    operand operand_;
};

/// 冪乗演算
//
/// 他の2項演算とは結合方向が異なる
struct exp_operation
{
    operand first;
    boost::optional<operand> rest;
};

/// 式
struct expression
{
    operand first;
    std::list<operation> rest;
};

/// シンボル(関数名)
struct symbol
{
    wchar_t first;
    std::list<wchar_t> rest;
};

/// 関数呼び出し
struct function_call
{
    symbol fun_name;
    operand first_arg;
    std::list<operand> rest_args;
};
} // namespace ast

BOOST_FUSION_ADAPT_STRUCT(ast::signed_,
    sign, operand_
)

BOOST_FUSION_ADAPT_STRUCT(ast::operation,
    operator_, operand_
)

BOOST_FUSION_ADAPT_STRUCT(ast::exp_operation,
    first, rest
)

BOOST_FUSION_ADAPT_STRUCT(ast::expression,
    first, rest
)

BOOST_FUSION_ADAPT_STRUCT(ast::function_call,
    fun_name, first_arg, rest_args
)

BOOST_FUSION_ADAPT_STRUCT(ast::symbol,
    first, rest
)

//============================================================
//
// AST evaluator
//

namespace ast {

/// AST evaluator
struct eval {
    typedef double result_type;

    double operator()(nil) const { BOOST_ASSERT(0); return 0; }
    double operator()(double n) const { return n; }

    double operator()(double lhs, operation const& x) const {
        double rhs = boost::apply_visitor(*this, x.operand_);
        switch (x.operator_)
        {
        case '+': return lhs + rhs;
        case '-': return lhs - rhs;
        case '*': return lhs * rhs;
        case '/': return lhs / rhs;
        }
        BOOST_ASSERT(0);
        return 0;
    }

    double operator()(signed_ const& x) const
        {
            double rhs = boost::apply_visitor(*this, x.operand_);
            switch (x.sign)
            {
            case '-': return -rhs;
            case '+': return +rhs;
            }
            BOOST_ASSERT(0);
            return 0;
        }

    double operator()(exp_operation const& x) const
        {
            double lhs = boost::apply_visitor(*this, x.first);
            if (x.rest) {
                double rhs = boost::apply_visitor(*this, x.rest.get());
                return pow(lhs, rhs);
            }
            return lhs;
        }

    double operator()(expression const& x) const
        {
            return std::accumulate(
                x.rest.begin(), x.rest.end()
                , boost::apply_visitor(*this, x.first)
                , *this);
        }
    double operator()(function_call const& x) const
        {
            std::wstring fun_name = (*this)(x.fun_name);
            std::vector<double> args;
            args.push_back(boost::apply_visitor(*this, x.first_arg));
            for (auto const& i : x.rest_args)
                args.push_back(boost::apply_visitor(*this, i));
            return BuiltInFunctions::Instance()(fun_name, args);
        }
    std::wstring operator()(symbol const& x) const
        {
            std::wstring result(1, x.first);
            for (auto i : x.rest)
                result += i;
            return result;
        }
};
} // namespace ast

//------------------------------------------------------------
//
/// 文法
//

namespace grammar {

using x3::double_;
using x3::standard_wide::char_;
using x3::standard_wide::lit;
using x3::standard_wide::alpha;
using x3::standard_wide::alnum;

x3::rule<class expression, ast::expression> const expression("式");
x3::rule<class term, ast::expression> const term("項");
x3::rule<class factor, ast::operand> const factor("因子");
x3::rule<class factor2, ast::exp_operation> const factor2("因子2");
x3::rule<class prim, ast::operand> const prim("原始");
x3::rule<class function_call, ast::function_call> const function_call("関数呼び出し");
x3::rule<class symbol, ast::symbol> const symbol("シンボル");

auto const expression_def =
    term
    >> *(   (char_(L'+') >> term)
        |   (char_(L'-') >> term)
        )
    ;

auto const term_def =
    factor
    >> *(   (char_(L'*') >> factor)
        |   (char_(L'/') >> factor)
        )
    ;

auto const factor_def =
        (char_(L'-') >> factor)
    |   (char_(L'+') >> factor)
    |   factor2
    ;

auto const factor2_def =
    prim
    >>  -((lit(L'^') | L"**") >> factor)
    ;

auto const prim_def =
        function_call
    |   double_
    |   L'(' >> expression >> L')'
    ;

auto const function_call_def =
    symbol
    >>   L'('
    >>   expression
    >>   *(L',' >> expression)
    >>   L')'
    ;

auto const symbol_def =
    alpha
    >>    *alnum
    ;

BOOST_SPIRIT_DEFINE(expression, term, factor, factor2, prim, function_call, symbol);
        
auto start = expression;

} // namespace grammer

//************************************************************

/// 一つの文字列を処理
double process(const wstring& str)
{
    ast::expression expression;             // Our expression (AST)

    auto iter = str.begin();
    auto end = str.end();
    boost::spirit::x3::standard_wide::space_type space;
    bool r = phrase_parse(iter, end, grammar::start, space, expression);

    if (r && iter == end) {
        return ast::eval{}(expression);
    }
    else {
        std::wstring rest{iter, end};
        wostringstream oss;
        oss << L"構文解析エラー: " << rest;
        throw runtime_error(to_utf8(oss.str()));
    }
}

//------------------------------------------------------------

/// エラーメッセージ
thread_local wstring ErrorMessage;
/// エラーメッセージ ANSI(MBCS) 版
thread_local string ErrorMessageA;

/// 計算式文字列を受け取って評価して返す
//
/// エラー時は NaN が返される。 \n
/// C/C++ では isnan マクロ/インラインテンプレート関数で判定できる。 \n
/// VB.NET, C# では Double.IsNaN メソッドで判定できる。 \n
/// NaN が返された場合でも、エラーメッセージは空の場合がある。
double __stdcall SHIKI_NO_KEISAN_Eval(const wchar_t* mathExpr)
{
    try {
        return process(mathExpr);
    }
    catch (const exception& x) {
        ErrorMessage = to_wide(x.what());
        return nan("");
    }
}

/// 計算式文字列を受け取って評価して返す ANSI(MBCS) 版
double __stdcall SHIKI_NO_KEISAN_EvalA(const char* mathExpr)
{
    return SHIKI_NO_KEISAN_Eval(to_wide(mathExpr).c_str());
}

/// エラーメッセージをクリア
void __stdcall SHIKI_NO_KEISAN_ClearErrorMessage()
{
    ErrorMessage.clear();
}

/// エラーメッセージへの参照を返す
//
/// 静的なバッファ上のエラーメッセージのポインタを返す。 \n
/// 空文字列のこともある。 \n
/// VB.NET, C# では IntPtr で受け取り、
/// Runtime.InteropServices.Marshal.PtrToStringAuto で String に変換する。
const wchar_t* __stdcall SHIKI_NO_KEISAN_GetErrorMessage()
{
    return ErrorMessage.c_str();
}

/// エラーメッセージへの参照を返す ANSI(MBCS) 版
const char* __stdcall SHIKI_NO_KEISAN_GetErrorMessageA()
{
    ErrorMessageA = to_acp(ErrorMessage);
    return ErrorMessageA.c_str();
}

/// 吸収相対誤差設定
//
/// 0 付近以外で吸収される誤差を設定します
//
/// \result 設定前の値
double __stdcall SHIKI_NO_KEISAN_SetRelativeToleranceAtTruncating(double e)
{
    double result = BuiltInFunctions::Instance().RelativeToleranceAtTruncating();
    BuiltInFunctions::Instance().SetRelativeToleranceAtTruncating(e);
    return result;
}

/// 吸収相対誤差取得
//
/// 0 付近以外で吸収される誤差を取得します
double __stdcall SHIKI_NO_KEISAN_GetRelativeToleranceAtTruncating()
{
    return BuiltInFunctions::Instance().RelativeToleranceAtTruncating();
}

/// 吸収絶対誤差設定
//
/// 0 付近で吸収される誤差を設定します
//
/// \result 設定前の値
double __stdcall SHIKI_NO_KEISAN_SetAbsoluteToleranceAtTruncating(double e)
{
    double result = BuiltInFunctions::Instance().AbsoluteToleranceAtTruncating();
    BuiltInFunctions::Instance().SetAbsoluteToleranceAtTruncating(e);
    return result;
}

/// 吸収絶対誤差取得
//
/// 0 付近で吸収される誤差を取得します
double __stdcall SHIKI_NO_KEISAN_GetAbsoluteToleranceAtTruncating()
{
    return BuiltInFunctions::Instance().AbsoluteToleranceAtTruncating();
}

/// 識別用メッセージ(ANSI) 保存静的バッファ
thread_local string IdentMessageA;

/// 識別用メッセージ(ANSI)
const char* __stdcall SHIKI_NO_KEISAN_GetIdentMessageA()
{
    ostringstream os;
    //
#ifdef PROJECT_VERSION
    static const char projectVersion[] = "$ProjectVersion: " PROJECT_VERSION " $";
    os << projectVersion << endl;
#endif
    //
#ifdef CONFIG_USE_STATIC_RUNTIME_LIBRARY
    static const char runtimeLibrary[] = "$RuntimeLibrary: Static $";
#else    
    static const char runtimeLibrary[] = "$RuntimeLibrary: Dynamic $";
#endif    
    os << runtimeLibrary << endl;
    //
#if defined(CONFIG_CMAKE_VERSION_STR)
    static const char identCmakeVersion[] = "$CmakeVersion: " CONFIG_CMAKE_VERSION_STR " $";
    os << identCmakeVersion << endl;
#endif
    //
#if defined(CONFIG_COMPILER_VERSION)
    static const char identCmakeCompilerVersion[] = "$CmakeCompilerVersion: " CONFIG_COMPILER_VERSION " $";
    os << identCmakeCompilerVersion << endl;
#endif
//        
#if defined(_MSC_FULL_VER)
    static const char identCompilerVersion[] = "$CompilerVersion: " BOOST_PP_STRINGIZE(_MSC_FULL_VER) " (_MSC_FULL_VER) $";
    os << identCompilerVersion << endl;
#endif
    //
#if defined(_MSVC_LANG)
    static const char identCppVersion[] = "$CppVersion: " BOOST_PP_STRINGIZE(_MSVC_LANG) " (_MSVC_LANG) $";
    os << identCppVersion << endl;
#endif
    //
#if defined(BOOST_VERSION)
    static const char identBoostVersion[] = "$BoostVersion: " BOOST_PP_STRINGIZE(BOOST_VERSION) " $";
    os << identBoostVersion << endl;
#endif
    //
#if defined(_M_X64)
    static const char identArch[] = "$Arch: x64 $";
#elif defined(_M_IX86)
    static const char identArch[] = "$Arch: x86 $";
#elif defined(_M_ARM64)
    static const char identArch[] = "$Arch: arm64 $";
#elif defined(_M_ARM)
    static const char identArch[] = "$Arch: arm $";
#else    
    static const char identArch[] = "$Arch: otherwise $";
#endif
    os << identArch << endl;
    //
#ifndef NDEBUG
    static const char identDebug[] = "$Debug: true $";
    os << identDebug << endl;
#endif
    IdentMessageA = os.str();
    return IdentMessageA.c_str();
}

//------------------------------------------------------------

// end of <shiki_no_keisan.cpp>
