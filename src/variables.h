// <variables.h> -*- coding: utf-8 -*-
//
// Project shiki-no-keisan-dll

// Copyright (C) 2024 neige68
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  https://www.boost.org/LICENSE_1_0.txt)

/// \file
/// \brief variables
//
// Compiler: VC14.2
//

#ifndef variables_h
#define variables_h

#include <map>                  // std::map
#include <string>               // std::wstring
#include <utility>              // std::swap

//------------------------------------------------------------
//
/// \class Variables
//
/// 変数の名前から値へのマップのシングルトンクラス
//

class Variables {

    // *** singleton ***
private:
    Variables() {}
public:
    /// シングルトン参照
    static Variables& Instance();

    // *** functions ***
public:
    void set(const std::wstring& name, double value) { map_[name] = value; }
    double replace(const std::wstring& name, double value) { std::swap(map_[name], value); return value; }
    double get(const std::wstring& name) const { return map_.at(name); }
    bool defined(const std::wstring& name) const { return map_.count(name); }

    // *** data ***
private:
    std::map<std::wstring, double> map_;

};

//------------------------------------------------------------

#endif // variables_h

// end of <variables.h>
