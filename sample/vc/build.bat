@rem <build.bat> -*- coding: cp932-dos -*- - build script
@echo off
rem
rem Project shiki-no-keisan-dll/sample/vc

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
set @exec_cmake=

set INCLUDE=../../include

rem ------------------------------------------------------------
rem
rem コンパイラ指定
rem

rem 環境変数 VC に vcvarsall.bat のあるディレクトリを指定
rem 環境変数 CMAKE_GEN に cmake が受け入れる Generator-name を指定

rem VC142: Visual Studio 16 2019
set VC=%VC142%
rem set VC=C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build
set CMAKE_GEN="Visual Studio 16 2019"

rem VC143: Visual Studio 17 2022
rem set VC=%VC143%
rem set VC=c:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build
rem set CMAKE_GEN="Visual Studio 17 2022"

rem ------------------------------------------------------------

:optloop
if "%1"=="" goto optend
if "%1"=="cm" set @exec_cmake=t
if "%1"=="cm" goto optnext
echo WARN: build.bat: オプション %1 が無効です.
:optnext
shift
goto optloop
:optend

if "%VCToolsVersion%"=="" call "%VC%\vcvarsall.bat" x86

rem **********
rem x86
set @BUILD=build
set @BIN=..\..\bin\x86
set LIB=..\..\..\lib\x86
set @CMAKE_OPT=-G %CMAKE_GEN% -A Win32 
call :common

rem **********
rem x64
set @BUILD=build64
set @BIN=..\..\bin\x64
set LIB=..\..\..\lib\x64
set @CMAKE_OPT=-G %CMAKE_GEN% -A x64
call :common
goto pop1_end

rem **********
rem common
:common
if not exist %@BUILD% mkdir %@BUILD%
pushd %@BUILD%
if not exist ALL_BUILD.vcxproj set @exec_cmake=t
if not "%@exec_cmake%"=="" cmake %@CMAKE_OPT% ..
msbuild ALL_BUILD.vcxproj /p:Configuration=Debug /m
echo INFO: build.bat: msbuild Debug Done.
if errorlevel 1 goto common_end
msbuild ALL_BUILD.vcxproj /p:Configuration=Release /m
echo INFO: build.bat: msbuild Release Done.
:common_end
popd
goto :EOF

:err
popd
:pop1_end

popd
if errorlevel 1 echo エラーがあります.
if errorlevel 1 exit /b 1
rem end of build.bat
