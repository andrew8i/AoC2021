cmake_minimum_required(VERSION 3.17)

project(Day1 LANGUAGES C)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_executable(day1 day1.c)