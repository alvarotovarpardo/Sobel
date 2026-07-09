#include "filter_selector.h"
#include <stdexcept>

std::unique_ptr<FilterBase> FilterSelector::createFilter(const EnumFilterType filterType)
{
    switch(filterType)
    {
        case FILTER_SOBEL:
            return std::make_unique<FilterSobel>();
        case FILTER_NONE:
        default:
            return nullptr;
    }
}

std::unique_ptr<FilterBase> FilterSelector::createFilter(const std::string& filterName)
{

    if (filterName == "sobel" || filterName == "SOBEL") {
        return createFilter(FILTER_SOBEL);
    }
        
    throw std::invalid_argument("Unknown filter " + filterName);
}