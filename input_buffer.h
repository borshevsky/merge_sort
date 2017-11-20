#pragma once

#include <cassert>
#include <string>
#include <vector>
#include <fstream>

class InputBuffer {
public:
    struct ReadResult {
        bool success;
        std::string value;
    };

    InputBuffer(std::string filename, size_t max_size);
    ReadResult read();
    void pop();

private:
    bool refill();

    std::ifstream fs_;
    std::string filename_;
    size_t max_size_;

    std::vector<std::string> buffer_;
};
