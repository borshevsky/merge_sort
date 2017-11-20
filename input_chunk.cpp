#include "input_chunk.h"

#include <iostream>

InputChunk::InputChunk(size_t max_size)
    : max_size_(max_size)
    , size_(0)
{}

bool InputChunk::try_add(const std::string &line)
{
    if (size_ + line.length() > max_size_) {
        return false;
    }

    size_ += line.length();
    lines_.push_back(line);

    return true;
}

void InputChunk::sort(Comparator comparator)
{
    std::sort(lines_.begin(), lines_.end(), comparator);
}

std::ostream& operator<<(std::ostream& os, const InputChunk& chunk)
{
    if (chunk.lines_.empty()) {
        return os;
    }

    for (size_t i = 0; i < chunk.lines_.size() - 1; ++i) {
        os << chunk.lines_[i] << '\n';
    }

    os << chunk.lines_.back();

    return os;
}
