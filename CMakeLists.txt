cmake_minimum_required(VERSION 3.11.0)

project(cuda-sample)
set(CMAKE_CXX_STANDARD 11)

# find_package(Boost)
set(source_files main.cc gpu.hpp gpu.cu gpu.cc varcolumn.h varcolumn.cpp varcolumn.cu)

find_package(CUDA)
# enable_language("CUDA")

SET (CUDA_NVCC_FLAGS "--gpu-architecture sm_20"  CACHE STRING "nvcc flags" FORCE)
SET (CUDA_VERBOSE_BUILD ON CACHE BOOL "nvcc verbose" FORCE) 

include_directories("${CUDA_TOOLKIT_ROOT_DIR}/include")
cuda_add_executable(cuda-sample ${source_files})

# target_link_libraries(cuda-sample ${CUDA_CUDART_LIBRARY})

