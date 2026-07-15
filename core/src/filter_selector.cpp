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

std::unique_ptr<FilterBase> FilterSelector::createFilter(std::string& filterName)
{
    LOG(filterName + std::string(" filter selected."));
    std::transform(filterName.begin(), filterName.end(), filterName.begin(), [](unsigned char c){return std::tolower(c);});
    if (filterName == "sobel") {
        return createFilter(FILTER_SOBEL);
    }
    LOG("Unknown filter.");    
    throw std::invalid_argument("Unknown filter " + filterName);
}