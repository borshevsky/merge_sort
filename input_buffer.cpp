#include "input_buffer.h"

#include <iostream>

InputBuffer::InputBuffer(std::string filename, size_t max_size)
    : fs_(filename)
    , filename_(filename)
    , max_size_(max_size)
{}

InputBuffer::ReadResult InputBuffer::read()
{
    if (buffer_.empty()) {
        if (!refill()) {
            return {false, ""};
        }
    }

    assert(!buffer_.empty());
    ReadResult ret {true, buffer_.back()};
    return ret;
}

void InputBuffer::pop()
{
    assert(!buffer_.empty());
    buffer_.pop_back();
}

bool InputBuffer::refill()
{
    if (!fs_) {
        return false;
    }

    assert(buffer_.empty());

    size_t read = 0;
    for (std::string line; std::getline(fs_, line);) {
        if (line.length() > max_size_) {
            // Do not sort lines larger than memory size
            throw std::runtime_error("There is no enough memory for read line");
        }

        if (line.length() + read > max_size_) {
            // Best API ever...
            if (fs_.eof()) {
                fs_.clear();
                fs_.seekg(-line.length(), std::ios::end);
            } else {
                fs_.seekg(-line.length() - 1, std::ios::cur);
            }

            break;
        }

        read += line.length();
        buffer_.push_back(std::move(line));
    }

    std::reverse(buffer_.begin(), buffer_.end());
    return !buffer_.empty();
}
