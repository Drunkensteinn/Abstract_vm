cmake_minimum_required(VERSION 3.14)
project(AbstractVM)

set(CMAKE_CXX_STANDARD 17)
include_directories(/Users/ablizniu/.brew/Cellar/boost/1.71.0/include/)

add_executable(AbstractVM src/main.cpp src/lexer.cpp inc/lexer.h src/parser.cpp inc/parser.h inc/IOperands.h src/Error.cpp inc/Error.h inc/IVm.h inc/Error_messages.h)