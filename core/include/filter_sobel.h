#pragma once
#include "filter_base.h"
#include <cmath>
#include <omp.h>
#include <algorithm>
#include <iostream>
#include <vector>

class FilterSobel : public FilterBase {
public:
    Image applyFilter(const Image& inputImage) override;
};