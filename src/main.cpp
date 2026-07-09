#include <iostream>
#include <filesystem>
#include "filter_selector.h"

int main(int argc, char** argv)
{
    std::string filterName = "sobel";
    if (argc > 1) {
        filterName = argv[1];
    }

    try {
        std::unique_ptr<FilterBase> pFilter = FilterSelector::createFilter(filterName);

        if (pFilter) {
            // Image img = ...;
            // Image out = pFilter->applyFilter(img);
        } else {
            std::cerr << "Null filter selected" << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Execution error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}