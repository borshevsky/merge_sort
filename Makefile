MEGABYTE = 1048576

CXX = g++
CXXFLAGS = -Wall -Wpedantic -Wextra -std=c++14 -DMEMORY_LIMIT=$(MEGABYTE)

external_merge: \
	chunk_sorting.o external_merge.o input_buffer.o \
	input_buffers_tracker.o input_chunk.o main.o output_buffer.o
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@


clean:
	rm *.o
	rm external_merge

run:
	./external_merge input

generate_data:
	./generator.py input 100000 1000

all: generate_data external_merge run

default: all
