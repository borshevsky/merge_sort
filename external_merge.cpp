#include "external_merge.h"
#include "input_buffer.h"
#include "input_buffers_tracker.h"
#include "output_buffer.h"

#include <iostream>
#include <sstream>

namespace impl {

ExternalMerge::ExternalMerge(
    std::vector<std::string> chunks, size_t memory_limit, Comparator cmp)
    : chunks_(std::move(chunks))
    , memory_limit_(memory_limit)
    , cmp_(std::move(cmp))
{}

std::string ExternalMerge::operator()()
{
    for (size_t i = 0; i < passes_count(); ++i) {
        pass(i);
    }

    return chunks_.front();
}

void ExternalMerge::pass(size_t pass_number)
{
    size_t chunks_count = chunks_at_time(pass_number);

    std::vector<std::string> new_chunks;
    for (size_t processed = 0, in_pass_number = 0;
         processed < chunks_.size();
         processed += chunks_count, ++in_pass_number
     ) {
        auto first = chunks_.begin() + processed;
        auto to_process = std::min(chunks_count, chunks_.size() - processed);

        std::vector<std::string> current_chunks = {first, first + to_process};
        new_chunks.push_back(merge(current_chunks, pass_number, in_pass_number));
    }

    std::swap(chunks_, new_chunks);
}

std::string ExternalMerge::merge(
    const std::vector<std::string>& chunks, size_t pass_number, size_t in_pass_number
) {
    auto output_name = make_merge_filename(pass_number, in_pass_number);

    std::cerr << "Will merge >> " << output_name << ": \n";
    for (const auto& chunk: chunks) {
        std::cerr << "  " << chunk << "\n";
    }

    size_t memory_limit_per_buffer = memory_limit_ / (chunks.size() + 1);

    std::vector<InputBuffer> input_buffers;
    input_buffers.reserve(chunks.size());
    for (const auto& chunk: chunks) {
        input_buffers.emplace_back(chunk, memory_limit_per_buffer);
    }

    InputBuffersTracker tracker(std::move(input_buffers), cmp_);

    OutputBuffer output(
        output_name,
        memory_limit_per_buffer);

    for (std::string line; tracker.retrieve_next_line(line);) {
        output.write(std::move(line));
    }

    return output_name;
}

size_t ExternalMerge::chunks_at_time(size_t pass_number) const
{
    if (pass_number == 0) {
        return chunks_.size() / 2;
    }

    return chunks_.size();
}

size_t ExternalMerge::passes_count() const
{
    return 2;
}

std::string ExternalMerge::make_merge_filename(
    size_t pass_number, size_t in_pass_number
) const {
    std::ostringstream ss;
    ss << "out_" << pass_number << "_" << in_pass_number;
    return ss.str();
}

} // namespace impl

std::string external_merge(
    std::vector<std::string> chunks, size_t memory_limit, Comparator comparator
) {
    impl::ExternalMerge external_merge(std::move(chunks), memory_limit, comparator);
    return external_merge();
}
