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
#include "variables.h"          // Variables

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

    // *** const ***
    /// 切捨時相対許容誤差予約変数名
    static inline const wchar_t* RelativeToleranceAtTruncatingVariableName = L"_RT";
    /// 切捨時絶対許容誤差予約変数名
    static inline const wchar_t* AbsoluteToleranceAtTruncatingVariableName = L"_AT";

    // *** singleton ***
private:
    BuiltInFunctions() {
        SetRelativeToleranceAtTruncating(1e-15);
        SetAbsoluteToleranceAtTruncating(1e-15);
    }
public:
    /// シングルトン参照
    static BuiltInFunctions& Instance();
    ~BuiltInFunctions() {}

    // *** functions ***
    /// 切捨時相対許容誤差の取得
    double RelativeToleranceAtTruncating() const
        { return Variables::Instance().get(RelativeToleranceAtTruncatingVariableName); }
    /// 切捨時相対許容誤差の設定
    double SetRelativeToleranceAtTruncating(double t)
        { return Variables::Instance().replace(RelativeToleranceAtTruncatingVariableName, t); }
    /// 切捨時絶対許容誤差の取得
    double AbsoluteToleranceAtTruncating() const
        { return Variables::Instance().get(AbsoluteToleranceAtTruncatingVariableName); }
    /// 切捨時絶対許容誤差の設定
    double SetAbsoluteToleranceAtTruncating(double t)
        { return Variables::Instance().replace(AbsoluteToleranceAtTruncatingVariableName, t); }
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
    /// 組み込み関数名前から関数へのマップ
    std::map<std::wstring, FunctionType> FunctionsMap;

};

//------------------------------------------------------------

#endif // bltinfun_h

// end of <bltinfun.h>
