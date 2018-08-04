#include "varcolumn.h"
#include <iostream>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <cuda_runtime.h>
#include <thrust/device_ptr.h>
#include <boost/core/demangle.hpp>
#include <boost/current_function.hpp>

varcolumn::varcolumn()
{
    std::cout << BOOST_CURRENT_FUNCTION << std::endl;
}

varcolumn::~varcolumn()
{
    std::cout << BOOST_CURRENT_FUNCTION << std::endl;
}

void
varcolumn::print()
{
    std::cout << BOOST_CURRENT_FUNCTION << std::endl;
    if (data) {
        thrust::device_ptr<double> dptr(reinterpret_cast<double*>(data.get()));
        if (dptr.get()) {
            auto val = thrust::raw_pointer_cast(dptr);
            std::cout << boost::core::demangle(typeid(val).name()) << std::endl;
            std::cout << *val << std::endl;
        }
        std::cout << "Has Data" << std::endl;
    } else {
        std::cout << "No Data to print" << std::endl;
    }
}

void
varcolumn::setData(std::size_t size, double value)
{
    data.reset(alloc(size, value), [&](void* d) { freeData(d); });
    elemCount = size;
    fillData(value);
}

void
varcolumn::freeData(void* data)
{
    std::cout << BOOST_CURRENT_FUNCTION << std::endl;

    if (data) {
        auto err = cudaFree(data);
        if (err != cudaSuccess) {
            cudaError_t lastErr = cudaGetLastError();
            std::cout << "Failed to free, with error code: " << lastErr << std::endl;
        }
    }
}

char*
varcolumn::alloc(std::size_t size, double value)
{
    cudaSetDevice(0);
    char* ret = nullptr;

    size_t byteCount = size * sizeof(double);

    auto err = cudaMalloc<char>(&ret, byteCount);
    if (err != cudaSuccess) {
        cudaError_t lastErr = cudaGetLastError();
        std::cout << "Error in allocating memory: Code: " << lastErr << std::endl;
    }

    // Determine free memory
    cudaDeviceSynchronize();
    size_t free, total;
    err = cudaMemGetInfo(&free, &total);
    if (err != cudaSuccess) {
        std::cout << "Error cudaMemGetInfo" << std::endl;
    } else {
        std::string allocDetail = "Free=" + std::to_string(free) + ", total= " + std::to_string(total);
        std::cout << allocDetail << std::endl;
    }

    std::cout << BOOST_CURRENT_FUNCTION << std::endl;

    return ret;
}
