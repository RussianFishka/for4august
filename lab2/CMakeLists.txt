cmake_minimum_required(VERSION 3.25)
project(lab2ta)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab2ta main.cpp AST/defast.h AST/defast.cpp AST/myNFA.h AST/myDFA.h)
