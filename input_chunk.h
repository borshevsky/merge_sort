#pragma once

#include "comparator.h"

#include <functional>
#include <iosfwd>
#include <vector>
#include <string>

class InputChunk {
public:
    explicit InputChunk(size_t max_size);

    bool try_add(const std::string& line);
    size_t size() const { return size_; }
    void sort(Comparator);
    friend std::ostream& operator<<(std::ostream& os, const InputChunk& chunk);

private:
    size_t max_size_;
    std::vector<std::string> lines_;
    size_t size_;
};
