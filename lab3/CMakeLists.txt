cmake_minimum_required(VERSION 3.25)
project(lab3ta)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab3ta lex.yy.c bisonpart.tab.h main.cpp myAst.h cellandother.h myAst.cpp usefulfunctions.h usefulfunctions.cpp myRobot.h myRobot.cpp)
