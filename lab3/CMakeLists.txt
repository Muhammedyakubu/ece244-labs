cmake_minimum_required(VERSION 3.20)
project(lab3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab3
	parser.cpp
	Shape.cpp
	Shape.h
	globals.h)
