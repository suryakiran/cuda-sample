cmake_minimum_required(VERSION 3.11.0)

project(cuda-sample)
set(CMAKE_CXX_STANDARD 14)

find_package(Boost COMPONENTS timer)
set(source_files main.cc gpu.hpp gpu.cu gpu.cc varcolumn.h varcolumn.cpp varcolumn.cu)

# set (CUDA_NVCC_FLAGS "--gpu-architecture sm_35"  CACHE STRING "nvcc flags" FORCE)

set(CMAKE_CUDA_SEPARABLE_COMPILATION ON)

enable_language("CUDA")
add_executable(cuda-sample ${source_files})

string(APPEND CMAKE_CUDA_FLAGS " -gencode=arch=compute_35,code=sm_35")
# string(APPEND CMAKE_CUDA_FLAGS_DEBUG " -lineinfo")
# message(${CMAKE_CUDA_FLAGS})

# set_source_files_properties(varcolumn.cu PROPERTIES CMAKE_CUDA_FLAGS " --device-debug;-lineinfo") 
# cuda_compile(F_OBJ ${f} OPTIONS --device-debug;-lineinfo )

target_link_libraries(cuda-sample PUBLIC Boost::chrono Boost::system)
target_compile_definitions(cuda-sample PUBLIC $<$<AND:$<COMPILE_LANGUAGE:CUDA>,$<CONFIG:DEBUG>>:THRUST_DEBUG>)
# target_compile_options(cuda-sample PUBLIC $<$<AND:$<COMPILE_LANGUAGE:CUDA>,$<CONFIG:DEBUG>>:-G>)
# target_compile_flags(cuda-sample PUBLIC $<$<COMPILE_LANGUAGE:CUDA>:"gencode=arch=compute_35,code=\"sm_35,compute_35\"">)
