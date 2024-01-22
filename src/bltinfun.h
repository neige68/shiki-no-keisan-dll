// <bltinfun.h> -*- coding: utf-8 -*-
//
// Project shiki-no-keisan-dll

// Copyright (C) 2024 neige68
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  https://www.boost.org/LICENSE_1_0.txt)

/// \file
/// \brief 組込関数
//
// Compiler: VC14.2
//

#ifndef bltinfun_h
#define bltinfun_h

#include "charconv.h"           // utf8, utf8tow

#include <map>                  // std::map
#include <utility>              // std::swap
#include <vector>               // std::vector

//------------------------------------------------------------
//
/// 組込関数のシングルトンクラス
//

class BuiltInFunctions {

    // *** types ***
public:
    /// 引数のベクタの型
    typedef std::vector<double> Args;
    /// 関数の型
    typedef double (*FunctionType)(Args const& args);

    // *** singleton ***
private:
    BuiltInFunctions() : RelativeToleranceAtTruncating_(1e-15), AbsoluteToleranceAtTruncating_(1e-15) {}
public:
    /// シングルトン参照
    static BuiltInFunctions& Instance();
    ~BuiltInFunctions() {}

    // *** functions ***
public:
    /// 切捨時相対許容誤差の取得
    double RelativeToleranceAtTruncating() const { return RelativeToleranceAtTruncating_; }
    /// 切捨時相対許容誤差の設定
    double SetRelativeToleranceAtTruncating(double t) { std::swap(RelativeToleranceAtTruncating_, t); return t; }
    /// 切捨時絶対許容誤差の取得
    double AbsoluteToleranceAtTruncating() const { return AbsoluteToleranceAtTruncating_; }
    /// 切捨時絶対許容誤差の設定
    double SetAbsoluteToleranceAtTruncating(double t) { std::swap(AbsoluteToleranceAtTruncating_, t); return t; }
    /// 組込関数追加
    void Add(std::wstring const& name, FunctionType fun)
        { FunctionsMap.insert(make_pair(name, fun)); }
    /// 組込関数適用
    double Apply(std::wstring const& name, Args const& args);
    /// 組込関数適用
    double operator()(std::wstring const& name, Args const& args)
        { return Apply(name, args); }

    // *** data ***
private:
    /// 切捨時相対許容誤差
    double RelativeToleranceAtTruncating_;
    /// 切捨時絶対許容誤差
    double AbsoluteToleranceAtTruncating_;
    /// 組み込み関数名前から関数へのマップ
    std::map<std::wstring, FunctionType> FunctionsMap;
    
};

//------------------------------------------------------------

#endif // bltinfun_h

// end of <bltinfun.h>
