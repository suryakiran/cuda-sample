#pragma once
#include <cstdint>
#include "varcolumn.h"

void      printCudaVersion();
void      initCuda();
varcolptr initData(std::size_t size, double value);
