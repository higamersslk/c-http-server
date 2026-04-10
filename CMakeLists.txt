cmake_minimum_required(VERSION 3.10.0)
project(Cserver VERSION 0.1.0 LANGUAGES C)

file(GLOB SRC "src/*.c")

include_directories(include)

add_executable(server ${SRC})