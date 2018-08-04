cmake_minimum_required(VERSION 3.11.0)

project(cuda-sample)
set(CMAKE_CXX_STANDARD 14)

find_package(Boost)
set(source_files main.cc gpu.hpp gpu.cu gpu.cc varcolumn.h varcolumn.cpp varcolumn.cu)

enable_language("CUDA")
add_executable(cuda-sample ${source_files})

target_link_libraries(cuda-sample PUBLIC Boost::boost)

