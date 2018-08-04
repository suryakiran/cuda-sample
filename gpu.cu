#include <iostream>
#include "gpu.hpp"
#include <cuda.h>
#include <cuda_runtime.h>

void printCudaVersion()
{
    int runtime_ver;
    cudaRuntimeGetVersion(&runtime_ver);
    std::cout << "CUDA Runtime version: " << runtime_ver << std::endl;

    int driver_ver;
    cudaDriverGetVersion(&driver_ver);
    std::cout << "CUDA Driver version: " << driver_ver << std::endl;
}
