@rem <dist.bat> -*- coding: cp932-dos -*-
@echo off
rem
rem Project shiki-no-keisan-dll

rem Copyright (C) 2024 neige68
rem Distributed under the Boost Software License, Version 1.0.
rem (See accompanying file LICENSE or copy at
rem  https://www.boost.org/LICENSE_1_0.txt)

rem Note: バイナリリリース作成
rem
rem Windows:   10 and later
rem

setlocal
title %~f0
pushd %~dp0

set @VER=
for /f %%a in (src/version.txt) do set @VER=%%a
if "%@VER%"=="" goto nover
echo INFO: dist.bat: Ver.%@VER%

set @dist=dist\shiki-no-keisan-dll-%@ver%
if not exist %@dist% mkdir %@dist%
replace dist_readme.md %@dist% /a
replace dist_readme.md %@dist% /u
replace dist_readme.html %@dist% /a
replace dist_readme.html %@dist% /u
replace LICENSE %@dist% /a
replace LICENSE %@dist% /u
if not exist %@dist%\docs mkdir %@dist%\docs
replace docs\builtin_functions.html %@dist%\docs /a
replace docs\builtin_functions.html %@dist%\docs /u
replace docs\*.md %@dist%\docs /a
replace docs\*.md %@dist%\docs /u
if not exist %@dist%\bin\x64 mkdir %@dist%\bin\x64
replace bin\x64\*.dll %@dist%\bin\x64 /a
replace bin\x64\*.dll %@dist%\bin\x64 /u
replace sample\vcpp\build64\Release\eval.exe %@dist%\bin\x64 /a
replace sample\vcpp\build64\Release\eval.exe %@dist%\bin\x64 /u
if not exist %@dist%\bin\x86 mkdir %@dist%\bin\x86
replace bin\x86\*.dll %@dist%\bin\x86 /a
replace bin\x86\*.dll %@dist%\bin\x86 /u
replace sample\vcpp\build\Release\eval.exe %@dist%\bin\x86 /a
replace sample\vcpp\build\Release\eval.exe %@dist%\bin\x86 /u
if not exist %@dist%\lib\x64 mkdir %@dist%\lib\x64
replace lib\x64\*.lib %@dist%\lib\x64 /a
replace lib\x64\*.lib %@dist%\lib\x64 /u
if not exist %@dist%\lib\x86 mkdir %@dist%\lib\x86
replace lib\x86\*.lib %@dist%\lib\x86 /a
replace lib\x86\*.lib %@dist%\lib\x86 /u
if not exist %@dist%\include mkdir %@dist%\include
replace include\*.h %@dist%\include /a
replace include\*.h %@dist%\include /u
if not exist %@dist%\sample mkdir %@dist%\sample
replace sample\*.bat %@dist%\sample /a
replace sample\*.bat %@dist%\sample /u
if not exist %@dist%\sample\cs mkdir %@dist%\sample\cs
replace sample\cs\*.bat %@dist%\sample\cs /a
replace sample\cs\*.bat %@dist%\sample\cs /u
replace sample\cs\*.cs %@dist%\sample\cs /a
replace sample\cs\*.cs %@dist%\sample\cs /u
replace sample\cs\*.nmake %@dist%\sample\cs /a
replace sample\cs\*.nmake %@dist%\sample\cs /u
if not exist %@dist%\sample\vb mkdir %@dist%\sample\vb
replace sample\vb\*.bat %@dist%\sample\vb /a
replace sample\vb\*.bat %@dist%\sample\vb /u
replace sample\vb\*.vb %@dist%\sample\vb /a
replace sample\vb\*.vb %@dist%\sample\vb /u
replace sample\vb\*.nmake %@dist%\sample\vb /a
replace sample\vb\*.nmake %@dist%\sample\vb /u
if not exist %@dist%\sample\vc mkdir %@dist%\sample\vc
replace sample\vc\*.bat %@dist%\sample\vc /a
replace sample\vc\*.bat %@dist%\sample\vc /u
replace sample\vc\*.c %@dist%\sample\vc /a
replace sample\vc\*.c %@dist%\sample\vc /u
replace sample\vc\CMakeLists.txt %@dist%\sample\vc /a
replace sample\vc\CMakeLists.txt %@dist%\sample\vc /u
if not exist %@dist%\sample\vcpp mkdir %@dist%\sample\vcpp
replace sample\vcpp\*.bat %@dist%\sample\vcpp /a
replace sample\vcpp\*.bat %@dist%\sample\vcpp /u
replace sample\vcpp\*.cpp %@dist%\sample\vcpp /a
replace sample\vcpp\*.cpp %@dist%\sample\vcpp /u
replace sample\vcpp\CMakeLists.txt %@dist%\sample\vcpp /a
replace sample\vcpp\CMakeLists.txt %@dist%\sample\vcpp /u
del /s %@dist%\*.*~

pushd %@dist%
set @arc=shiki-no-keisan-dll-%@ver%.zip
if exist ..\%@arc% del ..\%@arc%
7z a ..\%@arc%
popd
goto end

:nover
echo ERROR: dist.bat: バージョンが読み込めません.
:end
@rem end of <dist.bat>
