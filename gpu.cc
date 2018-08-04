#include "gpu.hpp"
#include <iostream>
#include <cuda_runtime.h>

#define LOG_INFO(str) std::cout << str << std::endl
#define LOG_ERROR(str) std::cout << str << std::endl

void
initCuda()
{
    cudaError_t cudaStatus;
    std::cout << "Initializing cuda" << std::endl;
    cudaStatus = cudaDeviceReset();

    int count;
    cudaStatus = cudaGetDeviceCount(&count);

    std::cout << "Number of devices: " << count << std::endl;
    cudaStatus = cudaSetDevice(0);

    if (cudaStatus != cudaSuccess) {
        std::cout << "Unable to set cuda device" << std::endl;
    }

    cudaError_t lastErr = cudaGetLastError();

    size_t      free, total;
    cudaError_t err = cudaMemGetInfo(&free, &total);
    if (err != cudaSuccess) {
        lastErr = cudaGetLastError();
        std::cout << "Error cudaMemGetInfo with code: " << lastErr << std::endl;
    } else {
        std::cout << "Free=" << free << ", total=" << total << std::endl;
    }

    cudaDeviceSynchronize();

    size_t  heapSize;
    size_t  DesiredHeapSize = 1024 * 1024 * 1024;
    int16_t nCudaDeviceCount;

    err = cudaDeviceGetLimit(&heapSize, cudaLimitMallocHeapSize);
    if (err != cudaSuccess) {
        lastErr = cudaGetLastError();
        LOG_INFO("Error cudaDeviceGetLimit wit code: " << lastErr);
    } else if (heapSize < DesiredHeapSize) {
        heapSize = DesiredHeapSize;
        err      = cudaDeviceSetLimit(cudaLimitMallocHeapSize, heapSize);
        if (err != cudaSuccess) {
            lastErr = cudaGetLastError();
            LOG_ERROR("1. Error cudaDeviceSetLimit wit code: " << lastErr);

            // Try setting it to lower limit
            heapSize = DesiredHeapSize / 2;  // Try 256 MB heap is needed
            err      = cudaDeviceSetLimit(cudaLimitMallocHeapSize, heapSize);
            if (err != cudaSuccess) {
                lastErr = cudaGetLastError();
                LOG_ERROR("2. Error cudaDeviceSetLimit wit code: " << lastErr);
                // Try setting it to lower limit
                heapSize = DesiredHeapSize / 4;  // Atleas 128 MB heap is needed
                err      = cudaDeviceSetLimit(cudaLimitMallocHeapSize, heapSize);
                if (err != cudaSuccess) {
                    lastErr = cudaGetLastError();
                    LOG_ERROR("3. Error cudaDeviceSetLimit wit code: " << lastErr);
                }
            }
        }
    }

    err = cudaDeviceGetLimit(&heapSize, cudaLimitMallocHeapSize);
    if (err != cudaSuccess) {
        lastErr = cudaGetLastError();
        LOG_ERROR("Error cudaMemGetInfo with code: " << lastErr);
    } else {
        LOG_INFO("Final heapSize= " << heapSize);
    }

    nCudaDeviceCount = count;
}

varcolptr
initData(std::size_t size, double value)
{
    auto ret = std::make_shared<varcolumn>();
    ret->setData(size, value);
    return ret;
}
