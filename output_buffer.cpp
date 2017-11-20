#include "output_buffer.h"

#include <cassert>

OutputBuffer::OutputBuffer(std::string filename, size_t max_size)
    : fs_(std::move(filename))
    , max_size_(max_size)
    , current_size_(0)
{}

OutputBuffer::~OutputBuffer()
{
    flush();
}

void OutputBuffer::write(std::string value)
{
    if (value.length() > max_size_) {
        throw std::runtime_error("There is no enough memory for write line");
    }

    if (current_size_ + value.length() > max_size_) {
        flush();
    }

    current_size_ += value.length();
    buffer_.push_back(std::move(value));
}

void OutputBuffer::flush()
{
    assert(fs_.good());

    if (!buffer_.empty()) {
        for (size_t i = 0; i < buffer_.size(); ++i) {
            fs_ << buffer_[i] << "\n";
        }

        //fs_ << buffer_.back();
    }

    buffer_.clear();
    current_size_ = 0;
}
