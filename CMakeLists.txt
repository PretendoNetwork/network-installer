cmake_minimum_required(VERSION 3.1)
set(CMAKE_TOOLCHAIN_FILE $ENV{DEVKITPRO}/wut/share/wut.toolchain.cmake)

project(juxt-patcher LANGUAGES C CXX)
include("${WUT_ROOT}/share/wut.cmake" REQUIRED)

add_executable(juxt-patcher
    main.cpp
    log.c
)

set_property(TARGET juxt-patcher PROPERTY CXX_STANDARD 20)
target_compile_options(juxt-patcher PRIVATE -Wall)

wut_create_rpx(juxt-patcher)
