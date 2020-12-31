cmake_minimum_required(VERSION 3.12)

project(libbps
    LANGUAGES CXX
)

add_library(libbps
    ${PROJECT_SOURCE_DIR}/source/libbps.cpp
    ${PROJECT_SOURCE_DIR}/source/crc32.cpp
)
add_library(libbps::libbps ALIAS libbps)
#set_property(TARGET wiiurpx PROPERTY CXX_STANDARD 20)

target_include_directories(libbps
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
    PRIVATE
        ${PROJECT_SOURCE_DIR}/source
)
