// <bltinfun.h> -*- coding: utf-8 -*-
//
// Project shiki-no-keisan-dll
// Copyright (C) 2024 neige68
//
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
    BuiltInFunctions() : RelativeErrorThreshold_(1e-15), AbsoluteErrorThreshold_(1e-15) {}
public:
    /// シングルトン参照
    static BuiltInFunctions& Instance();
    ~BuiltInFunctions() {}

    // *** functions ***
public:
    /// 相対誤差吸収のための閾値の取得
    double RelativeErrorThreshold() const { return RelativeErrorThreshold_; }
    /// 相対誤差吸収のための閾値の設定
    double SetRelativeErrorThreshold(double t) { std::swap(RelativeErrorThreshold_, t); return t; }
    /// 絶対誤差吸収のための閾値の取得
    double AbsoluteErrorThreshold() const { return AbsoluteErrorThreshold_; }
    /// 絶対誤差吸収のための閾値の設定
    double SetAbsoluteErrorThreshold(double t) { std::swap(AbsoluteErrorThreshold_, t); return t; }
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
    /// 相対誤差吸収のための閾値
    double RelativeErrorThreshold_;
    /// 絶対誤差吸収のための閾値
    double AbsoluteErrorThreshold_;
    /// 組み込み関数名前から関数へのマップ
    std::map<std::wstring, FunctionType> FunctionsMap;
    
};

//------------------------------------------------------------

#endif // bltinfun_h

// end of <bltinfun.h>
