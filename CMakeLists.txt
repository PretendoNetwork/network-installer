cmake_minimum_required(VERSION 3.1)
set(CMAKE_TOOLCHAIN_FILE $ENV{DEVKITPRO}/wut/share/wut.toolchain.cmake)

project(network-installer LANGUAGES C CXX)
include("${WUT_ROOT}/share/wut.cmake" REQUIRED)

add_executable(network-installer
    main.cpp
    rpx_patches/rpx_backup_strategy.cpp
    rpx_patches/rpx_backup.cpp
    rpx_patches/rpx_hashes.cpp
    rpx_patches/rpx_patch.cpp
    util/log.c
    util/titles.cpp
    util/iosu_fs.cpp
)

set_property(TARGET network-installer PROPERTY CXX_STANDARD 20)
target_compile_options(network-installer PRIVATE -Wall)
target_include_directories(network-installer PRIVATE
    .
)

add_subdirectory(ext/libiosuhax)
add_subdirectory(ext/wiiurpxlib)
target_include_directories(network-installer PRIVATE ext/picosha2)
target_link_libraries(network-installer libiosuhax::libiosuhax wiiurpxlib::wiiurpxlib)
wut_create_rpx(network-installer)
