#include "chunk_sorting.h"
#include "input_chunk.h"
#include "external_merge.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#ifndef MEMORY_LIMIT
#define MEMORY_LIMIT 1024
#endif

bool comparator(const std::string& lhs, const std::string& rhs)
{
    return lhs < rhs;
}

std::string external_sort(char* filename)
{
    std::cerr << "Will sort " << filename << "\n";
    size_t chunk_size = MEMORY_LIMIT / 2;
    std::ifstream is(filename);

    auto chunks = chunk_sorting(is, chunk_size, &comparator);
    return external_merge(std::move(chunks), MEMORY_LIMIT, &comparator);
}

int main(int /*argc*/, char *argv[])
{
    char* filename = argv[1];
    auto result_path = external_sort(filename);
    std::cout << "Result: " << result_path << "\n";
}
