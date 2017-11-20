#pragma once

#include <functional>
#include <string>

using Comparator = std::function<bool(const std::string&, const std::string&)>;
