cmake_minimum_required(VERSION 3.8.0)

project(n0va-crypto)

set(CMAKE_PREFIX_PATH "C:/Qt/5.15.1/mingw81_64")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core REQUIRED)

add_executable(n0va-crypto
    main.cc
    Qt-AES/qaesencryption.cpp
)

target_link_libraries(n0va-crypto Qt5::Core)