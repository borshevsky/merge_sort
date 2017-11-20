#include "input_buffers_tracker.h"

#include <iostream>

InputBuffersTracker::InputBuffersTracker(
    std::vector<InputBuffer> buffers,
    Comparator cmp)
    : cmp_(cmp)
    , last_results_()
{
    for (auto&& buffer: buffers) {
        auto read_result = buffer.read();
        last_results_.emplace_back(std::move(buffer), std::move(read_result));
    }
}

bool InputBuffersTracker::retrieve_next_line(std::string &line)
{
    clear();
    if (last_results_.empty()) {
        return false;
    }

    auto min_it = std::min_element(
        last_results_.begin(), last_results_.end(),
        [this] (const auto& lhs, const auto& rhs) {
            return cmp_(lhs.second.value, rhs.second.value);
        });

    min_it->first.pop();
    line = std::move(min_it->second.value);
    min_it->second = min_it->first.read();

    return true;
}

void InputBuffersTracker::clear()
{
    for (auto it = last_results_.begin(); it != last_results_.end();) {
        if (!it->second.success) {
            it = last_results_.erase(it);
        } else {
            it++;
        }
    }
}
