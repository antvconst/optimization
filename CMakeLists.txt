cmake_minimum_required(VERSION 3.8)

project(Optimization)


set(CMAKE_CXX_STANDARD 14)
add_compile_options(
  "-Wall" "-Wpedantic" "-Wextra" "-fexceptions"
  "-O0;-g3;-ggdb"
)
include_directories(math)

set(SOURCE_FILES main.cpp math/random/prng.cpp math/random/random.cpp math/basic/aaboxregion.cpp math/basic/point.cpp math/optimization/gradient_descent.cpp math/optimization/optimizer.cpp math/optimization/stochastic_search.cpp)

add_executable(optim-main ${SOURCE_FILES})