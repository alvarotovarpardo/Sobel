#pragma once
#include "image.h"

class FilterBase {
public:
    virtual ~FilterBase() = default;
    virtual Image applyFilter(const Image&) = 0;
};