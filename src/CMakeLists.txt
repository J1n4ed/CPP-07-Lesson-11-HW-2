cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(GuessWords)

#Для студии ставим флаг, что кодировка исходников UTF-8
#if(MSVC)
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
#endif()

set (SOURCES
hints.cpp
main.cpp
)

set (HEADERS
hints.h
)

add_executable(GuessWords ${SOURCES} ${HEADERS})
