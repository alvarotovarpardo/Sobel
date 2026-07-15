#pragma once

#include <memory>
#include <string>
#include <cctype>
#include "filter_sobel.h"

class FilterSelector {
public:
    enum EnumFilterType { FILTER_NONE, FILTER_SOBEL };
    static std::unique_ptr<FilterBase> createFilter(const EnumFilterType filterType);
    static std::unique_ptr<FilterBase> createFilter(std::string& filterName);
};