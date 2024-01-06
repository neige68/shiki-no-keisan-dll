@rem <build.bat> -*- coding: cp932-dos -*- - build all script
@echo off
rem
rem Project shiki-no-keisan-dll

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

call src\build.bat
if errorlevel 1 goto err
call sample\cs\build.bat
if errorlevel 1 goto err
call sample\vb\build.bat
if errorlevel 1 goto err
call sample\vc\build.bat
if errorlevel 1 goto err
call sample\vcpp\build.bat

:err
popd

rem end of build.bat
