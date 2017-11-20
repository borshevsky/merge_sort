#include "chunk_sorting.h"
#include "input_chunk.h"

#include <sstream>
#include <fstream>

namespace {

std::string make_chunk_fname(size_t chunk_number, size_t pass_number = 0)
{
    std::ostringstream ss;
    ss << "chunk_" << pass_number << "_" << chunk_number;
    return ss.str();
}

}

std::vector<std::string> chunk_sorting(std::istream& is, size_t chunk_size, Comparator comparator)
{
    size_t chunks_count = 0;

    std::vector<std::string> ret;
    while (is) {
        InputChunk chunk(chunk_size);

        for (;;) {
            std::string line;
            if (!std::getline(is, line)) {
                break;
            }

            if (!chunk.try_add(line)) {
                is.seekg(-line.length() - 1, std::ios::cur);
                break;
            }
        }

        chunk.sort(comparator);
        auto filename = make_chunk_fname(chunks_count++);
        std::ofstream(filename) << chunk;
        ret.push_back(filename);
    }

    return ret;
}
