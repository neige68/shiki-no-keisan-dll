# <CMakeLists.txt> -*- coding: utf-8 -*-
#
# Project shiki-no-keisan-dll
# Copyright (C) 2024 neige68
#

cmake_minimum_required(VERSION 3.24)

# スタティックランタイムライブラリ使用
if ($ENV{USE_STATIC_RUNTIME_LIBRARY})
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

project(shiki-no-keisan-dll CXX)

# バージョン
file(STRINGS version.txt PROJECT_VERSION)
message(STATUS "PROJECT_VERSION: ${PROJECT_VERSION}")

# PROJECT_VERSION=v0.v1 形式と仮定して分解する
string(REPLACE "." ";" VERSION_LIST ${PROJECT_VERSION})
list(GET VERSION_LIST 0 VER_MAJOR) # v0
list(GET VERSION_LIST 1 VER_MINOR) # v1
# 数値化することで 00 -> 0, 011 -> 11 のように先頭のゼロを削除
# この際0前置でも8進数評価でないことは確認済み
math(EXPR VER_MINOR ${VER_MINOR})
# 9,9,9,9 形式を生成する
set(VER_PRODUCTVERSION "${VER_MAJOR},${VER_MINOR},0,0")
message(STATUS "VER_PRODUCTVERSION: ${VER_PRODUCTVERSION}")

#------------------------------------------------------------
#
# boost
#

# BOOST を探す
# C: ドライブ以外から探すには 環境変数 CMAKE_PREFIX_PATH の設定が必要
find_package(Boost 1.81 REQUIRED COMPONENTS program_options)
message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

#------------------------------------------------------------

# C++17 使用
set(CMAKE_CXX_STANDARD "17")

# /MP: マルチプロセス
# /W4: 警告レベルを4とする
# /source-charset:utf-8: ソースコードを utf-8 とする
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /W4 /source-charset:utf-8")

# マップファイル生成
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /MAP")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /MAP")

# リソースコンパイラフラグ
set(CMAKE_RC_FLAGS "${CMAKE_RC_FLAGS} /DVER_PRODUCTVERSION=${VER_PRODUCTVERSION} /DPROJECT_VERSION=${PROJECT_VERSION}")
# CMAKE_GENERATOR_PLATFORM が x64 のときリソースコンパイラフラグに /D_WIN64 を追加
if (${CMAKE_GENERATOR_PLATFORM} STREQUAL "x64")
    set(CMAKE_RC_FLAGS "${CMAKE_RC_FLAGS} /D_WIN64")
endif ()

add_compile_definitions(PROJECT_VERSION=${PROJECT_VERSION})

include_directories(../include)

add_library(neige68.ShikiNoKeisan SHARED
    shiki_no_keisan.cpp bltinfun.cpp charconv.cpp version.rc)

enable_testing()

add_executable(test_exp test/test_exp.cpp)
target_compile_definitions(test_exp PRIVATE _USE_MATH_DEFINES)
target_link_libraries(test_exp neige68.ShikiNoKeisan)
add_test(NAME test_exp COMMAND test_exp)

add_executable(test_gamma test/test_gamma.cpp)
target_compile_definitions(test_gamma PRIVATE _USE_MATH_DEFINES)
target_link_libraries(test_gamma neige68.ShikiNoKeisan)
add_test(NAME test_gamma COMMAND test_gamma)

add_executable(test_max test/test_max.cpp)
target_compile_definitions(test_max PRIVATE _USE_MATH_DEFINES)
target_link_libraries(test_max neige68.ShikiNoKeisan)
add_test(NAME test_max COMMAND test_max)

add_executable(test_op test/test_op.cpp)
target_compile_definitions(test_op PRIVATE _USE_MATH_DEFINES)
target_link_libraries(test_op neige68.ShikiNoKeisan)
add_test(NAME test_op COMMAND test_op)

add_executable(test_rand test/test_rand.cpp)
target_compile_definitions(test_rand PRIVATE _USE_MATH_DEFINES)
target_link_libraries(test_rand neige68.ShikiNoKeisan)
add_test(NAME test_rand COMMAND test_rand)

add_executable(test_round test/test_round.cpp)
target_compile_definitions(test_round PRIVATE _USE_MATH_DEFINES)
target_link_libraries(test_round neige68.ShikiNoKeisan)
add_test(NAME test_round COMMAND test_round)

add_executable(test_sign test/test_sign.cpp)
target_compile_definitions(test_sign PRIVATE _USE_MATH_DEFINES)
target_link_libraries(test_sign neige68.ShikiNoKeisan)
add_test(NAME test_sign COMMAND test_sign)

add_executable(test_sqrt test/test_sqrt.cpp)
target_compile_definitions(test_sqrt PRIVATE _USE_MATH_DEFINES)
target_link_libraries(test_sqrt neige68.ShikiNoKeisan)
add_test(NAME test_sqrt COMMAND test_sqrt)

add_executable(test_triangle test/test_triangle.cpp)
target_compile_definitions(test_triangle PRIVATE _USE_MATH_DEFINES)
target_link_libraries(test_triangle neige68.ShikiNoKeisan)
add_test(NAME test_triangle COMMAND test_triangle)

# end of <CMakeLists.txt>
