// <eval.cpp> -*- coding: utf-8 -*-
//
// Project shiki-no-keisan-dll/sample/vc
// Copyright (C) 2024 neige68
//
/// \file
/// \brief サンプルプログラム
//
// Compiler: VC14.2
//

#include "shiki_no_keisan.h"

#include <boost/preprocessor/wstringize.hpp> // BOOST_PP_WSTRINGIZE
#include <boost/program_options.hpp> // boost::program_options
#include <boost/format.hpp>          // boost::format

#include <cstdlib>              // std::mbstowcs_s
#include <exception>            // std::exception
#include <iomanip>              // std::setprecision
#include <iostream>             // std::wcout
#include <sstream>              // std::ostringstream

using namespace std;

//------------------------------------------------------------

/// アクティブコードページ ナロー文字列を wstring に変換
wstring to_wide(const string& str)
{
    size_t returnValue;
    vector<wchar_t> wcstr(str.size()+1);
    mbstowcs_s(&returnValue, &wcstr.at(0), wcstr.size(), str.c_str(), wcstr.size() - 1);
    return &wcstr.at(0);
}

/// バージョン出力
void version()
{
    wcout << L"Eval";
#if defined(_WIN64)
    wcout << L" x64";
#else        
    wcout << L" x86";
#endif
#if defined(NDEBUG)
    wcout << L" Release";
#else
    wcout << L" Debug";
#endif
    wcout << L" Version";
}

/// ヘルプメッセージ出力
void help(const boost::program_options::options_description& opt)
{
    version();
    wcout << endl;
    wcout << L"書式: eval {オプション} 式 ..." << endl << endl;
    ostringstream oss;
    oss << opt;
    wcout << to_wide(oss.str()) << endl;
}

/// 一つの文字列を処理
void process(const wstring& str)
{
    SHIKI_NO_KEISAN_ClearErrorMessage();
    double ans = SHIKI_NO_KEISAN_Eval(str.c_str());
    const wchar_t* msg = SHIKI_NO_KEISAN_GetErrorMessage();
    if (msg && *msg)
        wcerr << L"ERROR: " << str << L" : " << msg << endl;
    else
        wcout << str << L" = " << ans << endl;
}

/// ワイド文字版C++メイン
int wmain(int argc, wchar_t** argv)
{
    try {
        locale::global(locale{locale{}, "", locale::ctype});
        namespace po = boost::program_options;
        po::positional_options_description p;
        p.add("input-text", -1);
        po::options_description hidden("hidden options");
        hidden.add_options()
            ("input-text", po::wvalue<vector<wstring>>(), "input text")
            ;
        po::options_description visible("オプション");
        visible.add_options()
            ("help,H", "ヘルプ")
            ("version,V", "バージョン表示")
            ("precision,P", po::wvalue<int>()->default_value(6), "出力精度")
            ("relative-error,R", po::wvalue<double>()->default_value(SHIKI_NO_KEISAN_GetRelativeErrorThreshold()), "吸収相対誤差")
            ("absolute-error,A", po::wvalue<double>()->default_value(SHIKI_NO_KEISAN_GetAbsoluteErrorThreshold()), "吸収絶対誤差")
            ;
        po::options_description opt("オプション");
        opt.add(visible).add(hidden);
        po::variables_map vm;
        store(po::basic_command_line_parser<wchar_t>(argc, argv).options(opt).positional(p).run(), vm);
        po::notify(vm);
        if (vm.count("help")) {
            help(visible);
            return 0;
        }
        if (vm.count("version")) {
            version();
            return 0;
        }
        if (vm.count("precision"))
            wcout << setprecision(vm["precision"].as<int>());
        if (vm.count("relative-error"))
            SHIKI_NO_KEISAN_SetRelativeErrorThreshold(vm["relative-error"].as<double>());
        if (vm.count("absolute-error"))
            SHIKI_NO_KEISAN_SetAbsoluteErrorThreshold(vm["absolute-error"].as<double>());
        //
        if (vm.count("input-text")) {
            for (const auto& str : vm["input-text"].as<vector<wstring>>()) {
                process(str);
            }
        }
        else {
            wstring str;
            while (getline(wcin, str)) {
                if (str.empty() || str == L".") break;
                process(str);
            }
        }
    }
    catch (const exception& x) {
        wcerr << L"ERROR: " << to_wide(x.what()) << endl;
    }
    return 0;
}

//------------------------------------------------------------

// end of <eval.cpp>
