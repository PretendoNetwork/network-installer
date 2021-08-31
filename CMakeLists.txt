cmake_minimum_required(VERSION 3.1)
set(CMAKE_TOOLCHAIN_FILE $ENV{DEVKITPRO}/wut/share/wut.toolchain.cmake)

project(network-installer LANGUAGES C CXX)
include("${WUT_ROOT}/share/wut.cmake" REQUIRED)

add_executable(network-installer
    main.cpp
    juxt.cpp
    cert_patches/cert_backup_strategy.cpp
    cert_patches/cert_backup.cpp
    cert_patches/cert_hashes.cpp
    menu/menu_done.cpp
    menu/menu_loading.cpp
    menu/menu_miiverse_confirm.cpp
    menu/menu.cpp
    rpx_patches/rpx_backup_strategy.cpp
    rpx_patches/rpx_backup.cpp
    rpx_patches/rpx_hashes.cpp
    rpx_patches/rpx_patch.cpp
    util/log.c
    util/titles.cpp
    util/iosu_fs.cpp
)
wut_create_rpx(network-installer)

set_property(TARGET network-installer PROPERTY CXX_STANDARD 20)
target_compile_options(network-installer PRIVATE -Wall)
target_include_directories(network-installer PRIVATE
    .
)

add_subdirectory(ext/libbps)
add_subdirectory(ext/libiosuhax)
add_subdirectory(ext/wiiurpxlib)
target_include_directories(network-installer PRIVATE ext/picosha2)
target_include_directories(network-installer PRIVATE ext/zstr/src)
target_link_libraries(network-installer PRIVATE libbps::libbps libiosuhax::libiosuhax wiiurpxlib::wiiurpxlib)

find_package(PkgConfig REQUIRED)
pkg_check_modules(zlib REQUIRED IMPORTED_TARGET zlib)

target_link_libraries(network-installer PRIVATE
    PkgConfig::zlib
)

#resinfs/romfs bits`
#kinda hacky but whatever
add_custom_command(
    OUTPUT app.romfs.o
    COMMAND tar -H ustar -cvf romfs.tar -C "${CMAKE_CURRENT_SOURCE_DIR}/assets" .
    COMMAND ${CMAKE_LINKER} --relocatable --format binary --output app.romfs.o romfs.tar
    COMMAND rm -f romfs.tar
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/assets"
)
set_source_files_properties(
    app.romfs.o
    PROPERTIES
    EXTERNAL_OBJECT true
    GENERATED true
)

target_sources(network-installer PRIVATE
    ext/resinfs/source/romfs.c
    app.romfs.o
)
target_include_directories(network-installer PRIVATE
    ext/resinfs/include
)
