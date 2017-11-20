#pragma once

#include "comparator.h"
#include "input_buffer.h"

#include <algorithm>
#include <list>
#include <utility>

class InputBuffersTracker {
public:
    InputBuffersTracker(
        std::vector<InputBuffer> buffers, Comparator cmp);

    bool retrieve_next_line(std::string& line);

private:
    void clear();

    Comparator cmp_;
    std::list<std::pair<InputBuffer, InputBuffer::ReadResult>> last_results_;
};
