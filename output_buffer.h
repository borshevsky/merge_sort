#pragma once

#include <fstream>
#include <vector>
#include <string>

class OutputBuffer {
public:
    OutputBuffer(std::string filename, size_t max_size);
    ~OutputBuffer();

    void write(std::string value);

private:
    void flush();

    std::ofstream fs_;
    size_t max_size_;
    size_t current_size_;

    std::vector<std::string> buffer_;
};
