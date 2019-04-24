cmake_minimum_required(VERSION 3.0)
project(SPAN_example)
set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME} example.cpp SPANParser.cpp)