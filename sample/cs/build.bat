@rem <build.bat> -*- coding: cp932-dos -*-
@echo off
rem
rem Project shiki-no-keisan-dll/sample/cs

rem Copyright (C) 2024 neige68
rem Distributed under the Boost Software License, Version 1.0.
rem (See accompanying file LICENSE or copy at
rem  https://www.boost.org/LICENSE_1_0.txt)

rem Note: build
rem
rem Windows:   10 and lator
rem

setlocal
pushd %~dp0
set @build=build

rem ------------------------------------------------------------
rem
rem コンパイラ指定
rem

rem 環境変数 VC に vcvarsall.bat のあるディレクトリを指定

rem VC142: Visual Studio 16 2019
set VC=%VC142%
rem set VC=C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build

rem VC143: Visual Studio 17 2022
rem set VC=%VC143%
rem set VC=c:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build

rem ------------------------------------------------------------

if "%INCLUDE%"=="" call "%VC%\vcvarsall.bat" x86

if not exist %@build% mkdir %@build%
nmake /f sample.nmake
echo build.bat: ************************************************************
echo build.bat: ** AnyCPU generated
echo build.bat: ************************************************************

rem end of build.bat
