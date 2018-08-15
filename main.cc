#include <iostream>

#include "gpu.hpp"

int
main()
{
    std::cout << "*********** Cuda Status Begin: ***********" << std::endl;
    initCuda();
    printCudaVersion();
    std::cout << "*********** Cuda Status End: ***********" << std::endl;

    auto col = initData(25500, 23.4);

    if (col) {
        std::cout << col->print() << std::endl;
    } else {
        std::cout << "No data to print" << std::endl;
    }

    return 0;
}
