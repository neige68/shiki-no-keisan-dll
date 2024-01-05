@rem <exec.bat> -*- coding: cp932-dos -*-
@echo off
rem
rem Project shiki-no-keisan-dll
rem Copyright (C) 2024 neige68
rem
rem Note: exec
rem
rem Windows:   10 and lator
rem

setlocal
pushd %~dp0
set @config=debug
set @name=
set @verbose=
set @build=build\x86
set @rd=
:loop
if "%1"=="--" goto optbreak
if "%1"=="rd" goto rd
if "%1"=="x64" goto x64
if "%1"=="64" goto x64
if "%1"=="6" goto x64
if "%1"=="r" goto rel
if "%1"=="-r" goto rel
if "%1"=="rel" goto rel
if "%1"=="d" goto deb
if "%1"=="-d" goto deb
if "%1"=="deb" goto deb
if "%1"=="v" goto verbose
if "%1"=="-v" goto verbose
if "%1"=="h" goto help
if "%1"=="-h" goto help
if "%1"=="--help" goto help
goto optend
:rd
set @rd=_rd
shift
goto loop
:x64
set @build=build\x64
shift
goto loop
:rel
set @config=release
shift
goto loop
:deb
set @config=debug
shift
goto loop
:verbose
set @verbose=t
shift
goto loop
:optbreak
shift
:optend
if not "%1"=="" set @name=%1
if "%@name%"=="" goto help
set @exe=..\%@build%%@rd%\%@config%\%@name%.exe
if not "%@verbose%"=="" echo INFO: %@exe%
shift
shift
%@exe% %0 %1 %2 %3 %4 %5 %6 %7 %8 %9
goto end
:help
echo usage: exec [rd] [x64] [v] [deb/rel] [--] name
:end
popd
rem end of exec.bat
