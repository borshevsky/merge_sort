#pragma once

#include "comparator.h"

#include <functional>
#include <vector>
#include <string>

namespace impl {

class ExternalMerge {
public:
    ExternalMerge(std::vector<std::string> chunks, size_t memory_limit, Comparator);
    std::string operator()();

private:
    void pass(size_t pass_number);
    std::string merge(
        const std::vector<std::string>& chunks, size_t pass_number, size_t in_pass_number);

    size_t chunks_at_time(size_t pass_number) const;
    size_t passes_count() const;

    std::string make_merge_filename(size_t pass_number, size_t in_pass_number) const;

    std::vector<std::string> chunks_;
    size_t memory_limit_;
    Comparator cmp_;
};

} // namespace impl

std::string external_merge(
    std::vector<std::string> chunks, size_t memory_limit, Comparator comparator);
