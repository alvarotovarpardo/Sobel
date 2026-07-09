#pragma once
#include "filter_base.h"

class FilterSobel : public FilterBase {
public:
    Image applyFilter(const Image& inputImage) override;
};