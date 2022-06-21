cmake_minimum_required(VERSION 3.20)
set (CMAKE_CXX_STANDARD_REQUIRED True)
set (CMAKE_EXPORT_COMPILE_COMMANDS True)
set (CMAKE_CXX_STANDARD 17)

project(rfc)

set (SOURCES src/main.cpp src/lexer.cpp src/parser.cpp)

add_executable(rfc ${SOURCES})
