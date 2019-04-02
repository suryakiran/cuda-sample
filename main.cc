#include <iostream>

#include <iostream>
#include <numeric>
#include <vector>
#include "gpu.hpp"

#ifdef WIN32
const std::string red;
const std::string green;
const std::string yellow;
const std::string cyan;
const std::string magenta;
const std::string reset;
#else
const std::string red("\033[0;31m");
const std::string redn("\033[1;91m");
const std::string green("\033[1;32m");
const std::string yellow("\033[1;33m");
const std::string cyan("\033[0;36m");
const std::string magenta("\033[0;35m");
const std::string reset("\033[0m");
#endif

int
main()
{
    std::cout << yellow << "*********** Cuda Status Begin: ***********" << reset << std::endl;
    std::cout << cyan;
    initCuda();
    printCudaVersion();
    std::cout << reset;
    std::cout << yellow << "*********** Cuda Status End: ***********" << reset << std::endl;

    imageTest();
    std::cout << redn << "%%%%%%%%%% TEST END %%%%%%%%%%" << reset << std::endl;

    std::vector<uint32_t> vi{1, 2, 3, 4, 5}, vo(5, 0);
    std::exclusive_scan(vi.begin(), vi.end(), vo.begin(), 23);

    for (auto v : vo) {
        std::cout << v << '\t';
    }
    std::cout << std::endl;
    return 0;
}
