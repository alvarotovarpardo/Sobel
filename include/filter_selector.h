#pragma once

#include <memory>
#include <string>
#include "filter_sobel.h"

class FilterSelector {
public:
    enum EnumFilterType { FILTER_NONE, FILTER_SOBEL };
    static std::unique_ptr<FilterBase> createFilter(const EnumFilterType filterType);
    static std::unique_ptr<FilterBase> createFilter(const std::string& filterName);
};