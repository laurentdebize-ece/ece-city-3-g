cmake_minimum_required(VERSION 3.23)
project(ECECity C)
set(CMAKE_C_STANDARD 99)


file(GLOB_RECURSE SOURCES "src/*.c")
include_directories("include")

add_executable(ECECity ${SOURCES})
