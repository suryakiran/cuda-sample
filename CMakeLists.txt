cmake_minimum_required(VERSION 3.14.0)

project(cuda-sample)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CUDA_STANDARD 14)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)

find_package(Boost)
set(source_files main.cc gpu.hpp gpu.cu gpu.cc varcolumn.h varcolumn.cpp varcolumn.cu)

enable_language("CUDA")

add_executable(cuda-sample ${source_files})

set_target_properties(cuda-sample PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
target_compile_options(cuda-sample PRIVATE $<$<COMPILE_LANGUAGE:CUDA>:-gencode arch=compute_30,code=sm_30>)
target_link_libraries(cuda-sample PUBLIC Boost::boost)
