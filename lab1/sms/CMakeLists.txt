cmake_minimum_required(VERSION 3.25)
project(sms)

set(CMAKE_CXX_STANDARD 20)

add_executable(sms main.cpp labstr.cpp labstr.h NumAnalitics.h NumAnalitics.cpp)
