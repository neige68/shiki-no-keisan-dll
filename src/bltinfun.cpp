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
/// 平方根
//
/// sqrt(x) で x の非負の平方根を返す。
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
/// 指数
//
/// exp(x) で e (ネイピア数) の x 乗を返す。
//
REGISTER_BUILT_IN_FUNCTION(exp, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() == 1)
        return exp(args[0]);
    throw runtime_error(to_utf8(L"関数 exp は1個の引数が必要です."));
});

//
/// 対数
//
/// log(x, b) で b を底とする x の対数を返す。 \n
/// 第2引数 b は省略可能でデフォルトの値は 10 である。したがってこのとき log は常用対数となる。
//
REGISTER_BUILT_IN_FUNCTION(log, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() == 1)
        return log10(args[0]);
    if (args.size() == 2)
        return log(args[0]) / log(args[1]);
    throw runtime_error(to_utf8(L"関数 log は1個か2個の引数が必要です."));
});

//
/// 自然対数
//
/// ln(x) で x の自然対数(底はネイピア数)を返す。
//
REGISTER_BUILT_IN_FUNCTION(ln, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() == 1)
        return log(args[0]);
    throw runtime_error(to_utf8(L"関数 ln は1個の引数が必要です."));
});

//
/// 常用対数
//
/// log10(x) で x の常用対数(底は 10)を返す。
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
/// 符号
//
/// sign(x) で x が正の時 1、0 のとき 0、負の時 -1 を返す。
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
/// 絶対値
//
/// abs(x) で x の絶対値を返す。
//
REGISTER_BUILT_IN_FUNCTION(abs, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() == 1)
        return abs(args[0]);
    throw runtime_error(to_utf8(L"関数 abs は1個の引数が必要です."));
});

//
/// 剰余
//
/// mod(x, y) で x を y で割った余りを返す。 \n
/// 関数値は x と同符号で、絶対値は y 未満となる。
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
/// 最大
//
/// max(x, ...) で x, ... の最大値を返す。
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
/// 最小
//
/// min(x, ...) で x, ... の最小値を返す。
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
/// 正弦
//
/// sin(x) で x の正弦を返す。\n
/// x の単位はラジアンとする。
//
REGISTER_BUILT_IN_FUNCTION(sin, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() == 1)
        return sin(args[0]);
    throw runtime_error(to_utf8(L"関数 sin は1個の引数が必要です."));
});

//
/// 余弦
//
/// cos(x) で x の余弦を返す。\n
/// x の単位はラジアンとする。
//
REGISTER_BUILT_IN_FUNCTION(cos, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() == 1)
        return cos(args[0]);
    throw runtime_error(to_utf8(L"関数 cos は1個の引数が必要です."));
});

//
/// 正接
//
/// tan(x) で x の正接を返す。\n
/// x の単位はラジアンとする。
//
REGISTER_BUILT_IN_FUNCTION(tan, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() == 1)
        return tan(args[0]);
    throw runtime_error(to_utf8(L"関数 tan は1個の引数が必要です."));
});

//
/// 逆正弦
//
/// asin(x) で x の逆正弦を返す。\n
/// 関数値は -π/2 ～ π/2 ラジアンの範囲となる。
//
REGISTER_BUILT_IN_FUNCTION(asin, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() == 1)
        return asin(args[0]);
    throw runtime_error(to_utf8(L"関数 asin は1個の引数が必要です."));
});

//
/// 逆余弦
//
/// acos(x) で x の逆余弦を返す。\n
/// 関数値は -π/2 ～ π/2 ラジアンの範囲となる。
//
REGISTER_BUILT_IN_FUNCTION(acos, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() == 1)
        return acos(args[0]);
    throw runtime_error(to_utf8(L"関数 acos は1個の引数が必要です."));
});

//
/// 逆正接
//
/// atan(x) で x の逆正接を返す。\n
/// 関数値は 0 ～ π ラジアンの範囲となる。
//
REGISTER_BUILT_IN_FUNCTION(atan, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() == 1)
        return atan(args[0]);
    throw runtime_error(to_utf8(L"関数 atan は1個の引数が必要です."));
});

//
/// 2引数逆正接
//
/// atan2(y, x) で x = r cos θ, y = r sin θ となる θ を返す。
/// 関数値は -π ～ π ラジアンの範囲となる。
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
/// 床関数(-∞方向丸め)
//
/// floor(x) で x を超えない最大の整数を返す。
//
REGISTER_BUILT_IN_FUNCTION(floor, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() == 1) {
        const auto ret = BuiltInFunctions::Instance().RelativeToleranceAtTruncating();
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
        return floor(x + BuiltInFunctions::Instance().AbsoluteToleranceAtTruncating());
    }
    throw runtime_error(to_utf8(L"関数 floor は1個の引数が必要です."));
});

//
/// 天井関数(+∞方向丸め)
//
/// ceil(x) で x を下回らない最小の整数を返す。
//
REGISTER_BUILT_IN_FUNCTION(ceil, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() == 1) {
        const auto ret = BuiltInFunctions::Instance().RelativeToleranceAtTruncating();
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
        return ceil(x - BuiltInFunctions::Instance().AbsoluteToleranceAtTruncating());
    }
    throw runtime_error(to_utf8(L"関数 ceil は1個の引数が必要です."));
});

//
/// 絶対値切り捨て(0方向丸め)
//
/// trunc(x) で x の絶対値を切り捨てて返す。
//
REGISTER_BUILT_IN_FUNCTION(trunc, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() == 1) {
        const auto ret = BuiltInFunctions::Instance().RelativeToleranceAtTruncating();
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
    const auto ret = BuiltInFunctions::Instance().RelativeToleranceAtTruncating();
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
/// 指定桁0方向丸め
//
/// rounddown(x, d) で d で指定した桁に x を0方向に丸めて返す。\n
/// \n
/// d 自体が小数の時は d を 0 方向に丸める。 \n
/// d が 0 (省略可能)のとき x を整数に丸める。 \n
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
    const auto ret = BuiltInFunctions::Instance().RelativeToleranceAtTruncating();
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
/// 指定桁0から離れる方向丸め
//
/// roundup(x, d) で d で指定した桁に x を0から離れる方向に丸めて返す。\n
/// \n
/// d 自体が小数の時は d を 0 方向に丸める。 \n
/// d が 0 (省略可能)のとき x を整数に丸める。 \n
///      正のときは小数点以下が d 桁になるように x を丸める。 \n
///      負のときは整数で下から d の絶対値分の桁数が 0 になるように x を丸める。
//
REGISTER_BUILT_IN_FUNCTION(roundup, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() != 1 && args.size() != 2)
        throw runtime_error(to_utf8(L"関数 roundup は1個か2個の引数が必要です."));
    int d = 0;
    if (args.size() == 2)
        d = static_cast<int>(args[1]);
    return roundup(args[0], d);
});

/// round の実装
double myround(double x, double d = 0)
{
    const auto ret = BuiltInFunctions::Instance().RelativeToleranceAtTruncating();
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
/// 指定桁四捨五入
//
/// round(x, d) で d で指定した桁に x を四捨五入で丸めて返す。\n
/// \n
/// d 自体が小数の時は d を 0 方向に丸める \n
/// d が 0 (省略可能)のとき x を整数に丸める。 \n
///      正のときは小数点以下が d 桁になるように x を丸める。 \n
///      負のときは整数で下から d の絶対値分の桁数が 0 になるように x を丸める。
//
REGISTER_BUILT_IN_FUNCTION(round, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() != 1 && args.size() != 2)
        throw runtime_error(to_utf8(L"関数 round は1個か2個の引数が必要です."));
    int d = 0;
    if (args.size() == 2)
        d = static_cast<int>(args[1]);
    return myround(args[0], d);
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
    if (x < BuiltInFunctions::Instance().AbsoluteToleranceAtTruncating()) // 0 とみなす
        return uniform_real_distribution<>{0.0, 1.0}(engine);
    int n = static_cast<int>(myround(x, 0));
    if (!forceFloat && fabs(x - n) < n * BuiltInFunctions::Instance().RelativeToleranceAtTruncating()) // 整数
        return uniform_int_distribution<>{0, n-1}(engine);
    return uniform_real_distribution<>{0.0, x}(engine);
}

//
/// 一様乱数
//
/// random(x) で、x が 0 のとき(省略可能) 区間 [0,1) の一様乱数系列のひとつの値を返す。\n
/// x が正の整数のとき整数 0..x-1 の一様乱数系列のひとつの値を返す。\n
/// x が正の非整数のとき 区間 [0,x) の一様乱数系列のひとつの値を返す。\n
/// 現在 x が負の時は 0 と同じ扱いになっているが変更の可能性がある。
//
REGISTER_BUILT_IN_FUNCTION(random, [] (BuiltInFunctions::Args const& args) -> double {
    double x = 0;
    if (args.size() > 1)
        throw runtime_error(to_utf8(L"関数 random は1個以下の引数が必要です."));
    if (args.size() == 1)
        x = args[0];
    return random(x);
});

//
/// 浮動小数点の一様乱数
//
/// frandom(x) で、x が 0 のとき(省略可能) 区間 [0,1) の一様乱数系列のひとつの値を返す。\n
/// x が正のとき 区間 [0,x) の一様乱数系列のひとつの値を返す。\n
/// 現在 x が負の時は 0 と同じ扱いになっているが変更の可能性がある。
//
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
/// ガンマ関数
//
/// gamma(x) で x のガンマ関数の値を返す。
//
REGISTER_BUILT_IN_FUNCTION(gamma, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() == 1)
        return boost::math::tgamma<double>(args[0]);
    throw runtime_error(to_utf8(L"関数 gamma は1個の引数が必要です."));
});

//
/// ガンマ自然対数
//
/// gammaln(x) で x のガンマ関数の値の絶対値の自然対数を返す。
/// 意味としては ln(abs(gamma(x))) に等しいが、オーバフローを回避して計算できる x の範囲が広い。
//
REGISTER_BUILT_IN_FUNCTION(gammaln, [] (BuiltInFunctions::Args const& args) -> double {
    if (args.size() == 1)
        return boost::math::lgamma<double>(args[0]);
    throw runtime_error(to_utf8(L"関数 gammaln は1個の引数が必要です."));
});

//============================================================

// end of <bltinfun.cpp>
