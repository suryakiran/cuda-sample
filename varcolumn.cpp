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
