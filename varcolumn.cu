#include "varcolumn.h"

#include <thrust/device_ptr.h>
#include <thrust/fill.h>

void
varcolumn::fillData(double val)
{
    thrust::device_ptr<double> dptr(static_cast<double*>(data.get()));
    thrust::fill(dptr, dptr + elemCount, val);
}