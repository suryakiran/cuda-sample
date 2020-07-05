#include <iostream>
#include <cuda.h>
#include <cuda_runtime.h>
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/scatter.h>
#include "gpu.hpp"

void
printCudaVersion()
{
    int runtime_ver;
    cudaRuntimeGetVersion(&runtime_ver);
    std::cout << "CUDA Runtime version: " << runtime_ver << std::endl;

    int driver_ver;
    cudaDriverGetVersion(&driver_ver);
    std::cout << "CUDA Driver version: " << driver_ver << std::endl;
}

void
thrustTest()
{
    std::cout << " ***** Thrust Test begin *****" << std::endl;
    // mark even indices with a 1; odd indices with a 0
    int                        values[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    thrust::device_vector<int> d_values(values, values + 10);

    // scatter all even indices into the first half of the
    // range, and odd indices vice versa
    int                        map[10] = {0, 5, 1, 6, 2, 7, 3, 8, 4, 9};
    thrust::device_vector<int> d_map(map, map + 10);
    thrust::device_vector<int> d_output(10);
    thrust::scatter(thrust::device, d_values.begin(), d_values.end(), d_map.begin(), d_output.begin());

    thrust::host_vector<int> out(d_output);
    for (auto item : out) {
        std::cout << item << '\t';
    }
    std::cout << std::endl;
    std::cout << " ***** Thrust Test end *****" << std::endl;
}
