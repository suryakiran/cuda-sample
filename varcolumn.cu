#include "varcolumn.h"

#include <thrust/device_ptr.h>
#include <thrust/device_vector.h>
#include <thrust/execution_policy.h>
#include <thrust/fill.h>
#include <boost/core/demangle.hpp>
#include <boost/current_function.hpp>
#include <boost/timer/timer.hpp>

void
varcolumn::fillData(double val)
{
    thrust::device_ptr<double> dptr(static_cast<double*>(data.get()));
    thrust::fill(dptr, dptr + elemCount, val);
}

double
varcolumn::print()
{
    double num{0};
    std::cout << BOOST_CURRENT_FUNCTION << std::endl;
    if (data) {
        cudaSetDevice(0);

        thrust::device_ptr<double>              dptr(reinterpret_cast<double*>(data.get()));
        thrust::device_vector<double>::iterator iter = dptr;
        double                                  result{0};
        {
            boost::timer::auto_cpu_timer t;
            result = thrust::reduce(thrust::device, iter, iter + elemCount, 0.0);
        }
        std::cout << "Result: " << result << std::endl;
        return result;
    } else {
        // std::cout << "No Data to print" << std::endl;
    }
    return num;
}
