@rem <clean.bat> -*- coding: cp932-dos -*-
@echo off
rem
rem Project shiki-no-keisan-dll

rem Copyright (C) 2024 neige68
rem Distributed under the Boost Software License, Version 1.0.
rem (See accompanying file LICENSE or copy at
rem  https://www.boost.org/LICENSE_1_0.txt)

rem Note: clean
rem
rem Windows:   XP and lator
rem

setlocal
pushd %~dp0
rmdir /s /q build
rmdir /s /q bin
rmdir /s /q lib
rmdir /s /q dist
rmdir /s /q sample\cs\build
rmdir /s /q sample\vb\build
rmdir /s /q sample\vc\build
rmdir /s /q sample\vc\build64
rmdir /s /q sample\vcpp\build
rmdir /s /q sample\vcpp\build64
popd

@rem end of <clean.bat>
