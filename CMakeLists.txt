cmake_minimum_required(VERSION 3.8)

project(Optimization)


set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES main.cpp)
add_compile_options(
  "-Wall" "-Wpedantic" "-Wextra" "-fexceptions"
  "-O0;-g3;-ggdb>"
)

include_directories(math)

add_executable(optim-main ${SOURCE_FILES})