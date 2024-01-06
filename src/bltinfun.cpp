// <bltinfun.cpp> -*- coding: utf-8 -*-
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

#include "bltinfun.h"

#include <boost/math/special_functions.hpp> // boost::math::gamma

#include <cmath>                // std::sqrt, ...
#include <random>               // std::random_device, std::default_random_engine
#include <stdexcept>            // std::runtime_error

using namespace std;

//============================================================
//
// singleton class BuiltInFunctions
//

//static
BuiltInFunctions& BuiltInFunctions::Instance()
{
    static BuiltInFunctions theInstance{};
    return theInstance;
}

double BuiltInFunctions::Apply(wstring const& name, Args const& args)
{
    auto i = FunctionsMap.find(name);
    if (i == FunctionsMap.end())
        throw runtime_error(to_utf8(L"関数 " + name + L" はサポートされていません."));
    return (*i->second)(args);
}

//
// end of singleton class BuiltInFunctions
//
//============================================================
//
// 組み込み関数
//

/// 組み込み関数登録
#define REGISTER_BUILT_IN_FUNCTION(name, expr) \
class reg_## name { \
public: \
    reg_ ## name() { \
        BuiltInFunctions::Instance().Add(L#name, expr); \
    } \
}; \
reg_## name inst_reg_ ## name;

//------------------------------------------------------------
//
/// 平方根 sqrt(x)
//
REGISTER_BUILT_IN_FUNCTION(sqrt, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() == 1)
        return sqrt(args[0]);
    throw runtime_error(to_utf8(L"関数 sqrt は1個の引数が必要です."));
});

//------------------------------------------------------------
//
// 指数・対数
//

//
/// exp(x)
//
REGISTER_BUILT_IN_FUNCTION(exp, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() == 1)
        return exp(args[0]);
    throw runtime_error(to_utf8(L"関数 exp は1個の引数が必要です."));
});

//
/// log(x[, b])
//
/// Excel 互換 \n
/// b のデフォルト値は 10
//
REGISTER_BUILT_IN_FUNCTION(log, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() == 1)
        return log10(args[0]);
    if (args.size() == 2)
        return log(args[0]) / log(args[1]);
    throw runtime_error(to_utf8(L"関数 log は1個か2個の引数が必要です."));
});

//
/// 自然対数 ln(x)
//
REGISTER_BUILT_IN_FUNCTION(ln, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() == 1)
        return log(args[0]);
    throw runtime_error(to_utf8(L"関数 ln は1個の引数が必要です."));
});

//
/// 常用対数 log10(x)
//
REGISTER_BUILT_IN_FUNCTION(log10, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() == 1)
        return log10(args[0]);
    throw runtime_error(to_utf8(L"関数 log10 は1個の引数が必要です."));
});

//------------------------------------------------------------
//
// 符号・絶対値・剰余
//

//
/// 符号 sign(x)
//
REGISTER_BUILT_IN_FUNCTION(sign, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() == 1) {
        const double x = args[0];
        if (x < 0)
            return -1;
        else if (x > 0)
            return 1;
        return x;
    }
    throw runtime_error(to_utf8(L"関数 sign は1個の引数が必要です."));
});

//
/// abs(x)
//
REGISTER_BUILT_IN_FUNCTION(abs, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() == 1)
        return abs(args[0]);
    throw runtime_error(to_utf8(L"関数 abs は1個の引数が必要です."));
});

//
/// 剰余 mod(x, y)
//
REGISTER_BUILT_IN_FUNCTION(mod, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() == 2)
        return fmod(args[0], args[1]);
    throw runtime_error(to_utf8(L"関数 mod は2個の引数が必要です."));
});

//------------------------------------------------------------
//
// 最大・最小
//

//
/// max(x, ...)
//
REGISTER_BUILT_IN_FUNCTION(max, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() < 1)
        throw runtime_error(to_utf8(L"関数 max は1個以上の引数が必要です."));
    double result = args[0];
    for (auto const& i : args)
        if (isnan(result) || result < i)
            result = i;
    return result;
});

//
/// min(x, ...)
//
REGISTER_BUILT_IN_FUNCTION(min, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() < 1)
        throw runtime_error(to_utf8(L"関数 min は1個以上の引数が必要です."));
    double result = args[0];
    for (auto const& i : args)
        if (isnan(result) || result > i)
            result = i;
    return result;
});

//------------------------------------------------------------
//
// 三角関数
//

//
/// sin(x)
//
REGISTER_BUILT_IN_FUNCTION(sin, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() == 1)
        return sin(args[0]);
    throw runtime_error(to_utf8(L"関数 sin は1個の引数が必要です."));
});

//
/// cos(x)
//
REGISTER_BUILT_IN_FUNCTION(cos, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() == 1)
        return cos(args[0]);
    throw runtime_error(to_utf8(L"関数 cos は1個の引数が必要です."));
});

//
/// tan(x)
//
REGISTER_BUILT_IN_FUNCTION(tan, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() == 1)
        return tan(args[0]);
    throw runtime_error(to_utf8(L"関数 tan は1個の引数が必要です."));
});

//
/// asin(x)
//
REGISTER_BUILT_IN_FUNCTION(asin, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() == 1)
        return asin(args[0]);
    throw runtime_error(to_utf8(L"関数 asin は1個の引数が必要です."));
});

//
/// acos(x)
//
REGISTER_BUILT_IN_FUNCTION(acos, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() == 1)
        return acos(args[0]);
    throw runtime_error(to_utf8(L"関数 acos は1個の引数が必要です."));
});

//
/// atan(x)
//
REGISTER_BUILT_IN_FUNCTION(atan, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() == 1)
        return atan(args[0]);
    throw runtime_error(to_utf8(L"関数 atan は1個の引数が必要です."));
});

//
/// atan2(y, x)
//
REGISTER_BUILT_IN_FUNCTION(atan2, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() == 2)
        return atan2(args[0], args[1]);
    throw runtime_error(to_utf8(L"関数 atan2 は2個の引数が必要です."));
});

//------------------------------------------------------------
//
// 端数調整
//

//
/// 床関数 -∞方向丸め floor(x) 
//
REGISTER_BUILT_IN_FUNCTION(floor, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() == 1) {
        const auto ret = BuiltInFunctions::Instance().RelativeErrorThreshold();
        auto x = args[0];
        if (x > 0.5) {
            if (x * ret < 0.5)
                x *= 1 + ret;
            return floor(x);
        }
        else if (x < -0.5) {
            if (x * ret > -0.5)
                x *= 1 - ret;
            return floor(x);
        }
        return floor(x + BuiltInFunctions::Instance().AbsoluteErrorThreshold());
    }
    throw runtime_error(to_utf8(L"関数 floor は1個の引数が必要です."));
});

//
/// 天井関数 +∞方向丸め ceil(x)
//
REGISTER_BUILT_IN_FUNCTION(ceil, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() == 1) {
        const auto ret = BuiltInFunctions::Instance().RelativeErrorThreshold();
        auto x = args[0];
        if (x > 0.5) {
            if (x * ret < 0.5)
                x *= 1 - ret;
            return ceil(x);
        }
        else if (x < -0.5) {
            if (x * ret > -0.5)
                x *= 1 + ret;
            return ceil(x);
        }
        return ceil(x - BuiltInFunctions::Instance().AbsoluteErrorThreshold());
    }
    throw runtime_error(to_utf8(L"関数 ceil は1個の引数が必要です."));
});

//
/// 0方向丸め trunc(x)
//
REGISTER_BUILT_IN_FUNCTION(trunc, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() == 1) {
        const auto ret = BuiltInFunctions::Instance().RelativeErrorThreshold();
        auto x = args[0];
        const auto ax = fabs(x);
        if (ax > 0.5) {
            if (ax * ret < 0.5)
                x *= 1 + ret;
            return trunc(x);
        }
        return trunc(x);
    }
    throw runtime_error(to_utf8(L"関数 trunc は1個の引数が必要です."));
});

/// rounddown の実装
double rounddown(double x, double d = 0)
{
    const auto ret = BuiltInFunctions::Instance().RelativeErrorThreshold();
    double e = 1;
    if (d != 0)
        e = pow(10, rounddown(d));
    auto axe = fabs(x) * e;
    if (axe * ret < 0.5)
        axe *= 1 + ret;
    auto y = floor(axe) / e;
    if (x < 0) y = -y;
    return y;
}

//
/// rounddown(x[, d])
//
/// Excel 互換 \n
/// d で指定した桁に x を0方向に丸める。 \n
//
/// d 自体が小数の時は d を 0 方向に丸める。 \n
/// d が 0 (デフォルト)のとき x を整数に丸める。 \n
///      正のときは小数点以下が d 桁になるように x を丸める。 \n
///      負のときは整数で下から d の絶対値分の桁数が 0 になるように x を丸める。
//
REGISTER_BUILT_IN_FUNCTION(rounddown, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() != 1 && args.size() != 2)
        throw runtime_error(to_utf8(L"関数 rounddown は1個か2個の引数が必要です."));
    int d = 0;
    if (args.size() == 2)
        d = static_cast<int>(args[1]);
    return rounddown(args[0], d);
});

/// roundup の実装
double roundup(double x, double d = 0)
{
    const auto ret = BuiltInFunctions::Instance().RelativeErrorThreshold();
    double e = 1;
    if (d != 0)
        e = pow(10, rounddown(d));
    auto axe = fabs(x) * e;
    if (axe * ret < 0.5)
        axe *= 1 - ret;
    auto y = ceil(axe) / e;
    if (x < 0) y = -y;
    return y;
}

//
/// roundup(x[, d])
//
/// Excel 互換 \n
/// d で指定した桁に x を0から離れる方向に丸める。 \n
//
/// d 自体が小数の時は d を 0 方向に丸める。 \n
/// d が 0 (デフォルト)のとき x を整数に丸める。 \n
///      正のときは小数点以下が d 桁になるように x を丸める。 \n
///      負のときは整数で下から d の絶対値分の桁数が 0 になるように x を丸める。
REGISTER_BUILT_IN_FUNCTION(roundup, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() != 1 && args.size() != 2)
        throw runtime_error(to_utf8(L"関数 roundup は1個か2個の引数が必要です."));
    int d = 0;
    if (args.size() == 2)
        d = static_cast<int>(args[1]);
    return roundup(args[0], d);
});

/// round の実装
double round(double x, double d = 0)
{
    const auto ret = BuiltInFunctions::Instance().RelativeErrorThreshold();
    double e = 1;
    if (d != 0)
        e = pow(10, rounddown(d));
    auto axe = fabs(x) * e;
    if (axe * ret < 0.5)
        axe *= 1 + ret;
    auto y = floor(axe + 0.5) / e;
    if (x < 0) y = -y;
    return y;
}

//
/// round(x[, d])
//
/// Excel 互換 \n
/// d で指定した桁に x を四捨五入で丸める。 \n
//
/// d 自体が小数の時は d を 0 方向に丸める \n
/// d が 0 (デフォルト)のとき x を整数に丸める。 \n
///      正のときは小数点以下が d 桁になるように x を丸める。 \n
///      負のときは整数で下から d の絶対値分の桁数が 0 になるように x を丸める。
//
REGISTER_BUILT_IN_FUNCTION(round, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() != 1 && args.size() != 2)
        throw runtime_error(to_utf8(L"関数 round は1個か2個の引数が必要です."));
    int d = 0;
    if (args.size() == 2)
        d = static_cast<int>(args[1]);
    return round(args[0], d);
});

//------------------------------------------------------------
//
// 乱数
//

/// random の実装
double random(double x, bool forceFloat = false)
{
    static random_device seed_gen{};
    static default_random_engine engine{seed_gen()};
    if (x < BuiltInFunctions::Instance().AbsoluteErrorThreshold()) // 0 とみなす
        return uniform_real_distribution<>{0.0, 1.0}(engine);
    int n = static_cast<int>(round(x, 0));
    if (!forceFloat && fabs(x - n) < n * BuiltInFunctions::Instance().RelativeErrorThreshold()) // 整数
        return uniform_int_distribution<>{0, n-1}(engine);
    return uniform_real_distribution<>{0.0, x}(engine);
}

/// 一様乱数 random([x])
//
/// 引数なしおよび x が 0 のとき [0,1) の一様乱数(x が負の時も今はここ)
/// x が正の整数のとき x 未満の非負整数の一様乱数
/// x が正の非整数のとき x 未満の正の数の一様乱数
REGISTER_BUILT_IN_FUNCTION(random, [] (BuiltInFunctions::Args const& args) -> double {
    double x = 0;
    if (args.size() > 1)
        throw runtime_error(to_utf8(L"関数 random は1個以下の引数が必要です."));
    if (args.size() == 1)
        x = args[0];
    return random(x);
});

/// 浮動小数点の一様乱数 frandom([x])
//
/// 引数なしおよび x が 0 のとき [0,1) の一様乱数(x が負の時も今はここ)
/// x が正のとき x 未満の正の数の一様乱数
REGISTER_BUILT_IN_FUNCTION(frandom, [] (BuiltInFunctions::Args const& args) -> double {
    double x = 0;
    if (args.size() > 1)
        throw runtime_error(to_utf8(L"関数 frandom は1個以下の引数が必要です."));
    if (args.size() == 1)
        x = args[0];
    return random(x, true);
});

//------------------------------------------------------------
//
// gamma
//

//
/// gamma(x)
//
REGISTER_BUILT_IN_FUNCTION(gamma, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() == 1)
        return boost::math::tgamma<double>(args[0]);
    throw runtime_error(to_utf8(L"関数 gamma は1個の引数が必要です."));
});

//
/// gammaln(x) = ln(abs(gamma(x)))
//
REGISTER_BUILT_IN_FUNCTION(gammaln, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() == 1)
        return boost::math::lgamma<double>(args[0]);
    throw runtime_error(to_utf8(L"関数 gammaln は1個の引数が必要です."));
});

//============================================================

// end of <bltinfun.cpp>
