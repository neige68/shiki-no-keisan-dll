# <CMakeLists.txt> -*- coding: utf-8 -*-
#
# Project shiki-no-keisan-dll/sample/vc
# Copyright (C) 2024 neige68
#

cmake_minimum_required(VERSION 3.24)
set(CMAKE_VERBOSE_MAKEFILE ON)
# スタティックリンク
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

project(sample C)

include_directories($ENV{INCLUDE})
link_directories($ENV{LIB})

# /MP: マルチプロセス
# /W4: 警告レベルを4とする
# /source-charset:utf-8: ソースコードを utf-8 とする
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MP /W4 /source-charset:utf-8")

# マップファイル生成
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /MAP")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /MAP")

add_executable(sample sample.c)
target_link_libraries(sample $ENV{LIB}/neige68.ShikiNoKeisan)

# end of <CMakeLists.txt>
