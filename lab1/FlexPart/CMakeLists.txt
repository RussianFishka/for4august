cmake_minimum_required(VERSION 3.25)
project(FlexPart)
set(CMAKE_CXX_STANDARD 20)

add_executable(FlexPart main.cpp lex.yy.cc NumAnalitics.h NumAnalitics.cpp)
