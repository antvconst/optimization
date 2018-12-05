cmake_minimum_required(VERSION 3.8)

project(Optimization)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 14)

add_compile_options(
  "-Wall" "-Wpedantic" "-Wextra" "-fexceptions" "-Wsuggest-override" "-Wnon-virtual-dtor"
  "-O0;-g3;-ggdb"
)

set(SOURCE_FILES random/prng.cpp random/random.cpp basic/aaboxregion.cpp basic/point.cpp optimization/gradient_descent.cpp optimization/optimizer.cpp optimization/stochastic_search.cpp)

add_library(optim ${SOURCE_FILES})

add_executable(optim-main main.cpp)
target_link_libraries(optim-main optim)