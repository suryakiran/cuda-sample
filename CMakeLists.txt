cmake_minimum_required(VERSION 3.14.0)

if (NOT "$ENV{CMAKE_TOOLCHAIN_FILE}" STREQUAL "")
  set(CMAKE_TOOLCHAIN_FILE "$ENV{CMAKE_TOOLCHAIN_FILE}" CACHE INTERNAL "Copied from environment variable")
endif()

project(cuda-sample)
set(CMAKE_CXX_STANDARD 17)

find_package(Boost)
set(source_files main.cc gpu.hpp gpu.cu gpu.cc varcolumn.h varcolumn.cpp varcolumn.cu)

set (CUDA_NVCC_FLAGS "--gpu-architecture sm_35"  CACHE STRING "nvcc flags" FORCE)

enable_language("CUDA")
add_executable(cuda-sample ${source_files})

target_link_libraries(cuda-sample PUBLIC Boost::boost)

