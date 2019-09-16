cmake_minimum_required(VERSION 3.14)
project(AbstractVM)

set(CMAKE_CXX_STANDARD 17)

add_executable(AbstractVM src/main.cpp src/lexer.cpp inc/lexer.h src/parser.cpp inc/parser.h src/IOperands.cpp inc/IOperands.h src/Error.cpp inc/Error.h)