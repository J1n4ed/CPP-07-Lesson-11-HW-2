cmake_minimum_required(VERSION 3.10)

project(GuessWords)

set (SOURCES
hints.cpp
main.cpp
)

set (HEADERS
hints.h
)

add_executable(GuessWords ${SOURCES} ${HEADERS})
