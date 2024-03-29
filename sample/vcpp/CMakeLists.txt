# <CMakeLists.txt> -*- coding: utf-8 -*-
#
# Project shiki-no-keisan-dll/sample/vc

# Copyright (C) 2024 neige68
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at
#  https://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.28)
set(CMAKE_VERBOSE_MAKEFILE ON)
# スタティックリンク
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

project(sample CXX)

#------------------------------------------------------------
#
# boost
#

# BOOST を探す
# C: ドライブ以外から探すには 環境変数 CMAKE_PREFIX_PATH の設定が必要
find_package(Boost 1.84 REQUIRED COMPONENTS program_options)
message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

#------------------------------------------------------------

include_directories($ENV{INCLUDE})
link_directories($ENV{MYLIB})

# C++17 使用
set(CMAKE_CXX_STANDARD "17")

# /MP: マルチプロセス
# /W4: 警告レベルを4とする
# /source-charset:utf-8: ソースコードを utf-8 とする
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /W4 /source-charset:utf-8")

# マップファイル生成
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /MAP")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /MAP")

add_executable(eval eval.cpp)
target_link_libraries(eval $ENV{MYLIB}/neige68.ShikiNoKeisan)

# end of <CMakeLists.txt>
