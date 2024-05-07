// <double_parser.h> -*- coding: utf-8 -*-
//
// Project shiki-no-keisan-dll

// Copyright (C) 2024 neige68
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  https://www.boost.org/LICENSE_1_0.txt)

/// \file
/// \brief 精度を改善した double (倍精度浮動小数点) パーサ
//
// Compiler: VC14.2
//

#ifndef double_parser_hpp
#define double_parser_hpp

#include <boost/spirit/home/x3.hpp>

#include <string>

//------------------------------------------------------------

namespace my_parser {

struct my_double_class {};
typedef boost::spirit::x3::rule<my_double_class, double> my_double_type;
constexpr my_double_type my_double = "my_double";

/// 文字列中の double の開始位置を保存しておく
extern thread_local std::wstring::const_iterator my_double_start;

constexpr auto my_double_save_start =
    [] (auto const& ctx) { my_double_start = _where(ctx).begin(); };

constexpr auto my_double_act =
    [] (auto& ctx) {
        _val(ctx) = std::stod(std::wstring(my_double_start, _where(ctx).begin()));
    };

constexpr auto my_double_def =
        boost::spirit::x3::eps     [my_double_save_start]
    >>  boost::spirit::x3::double_ [my_double_act]
    ;

BOOST_SPIRIT_DEFINE(my_double);

} // namespace my_parser

//------------------------------------------------------------

#endif // double_parser_hpp

// end of <double_parser.hpp>
