#pragma once

#include "comparator.h"

#include <vector>
#include <string>
#include <istream>

std::vector<std::string> chunk_sorting(
    std::istream& is, size_t chunk_size, Comparator comparator);
