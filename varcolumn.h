#pragma once

#include <memory>

namespace race {

class varcolumn
{
public:
    varcolumn();
    ~varcolumn();

private:
};

using varcolptr = std::shared_ptr<varcolumn>;

}  // namespace race
