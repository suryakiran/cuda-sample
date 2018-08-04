#pragma once

#include <memory>

class varcolumn
{
public:
    varcolumn();
    ~varcolumn();

    void print();
    void setData(std::size_t size, double value);

private:
    char* alloc(std::size_t size, double value);
    void  freeData(void* d);
    void  fillData(double val);

    std::shared_ptr<void> data;
    size_t                elemCount{0};
};

using varcolptr = std::shared_ptr<varcolumn>;
