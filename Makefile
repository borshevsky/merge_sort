_32_KILOBYTES = 32768

LIMIT ?= $(_32_KILOBYTES)
CXX = g++
CXXFLAGS = -Wall -Wpedantic -Wextra -std=c++14 -DMEMORY_LIMIT=$(LIMIT)

external_merge: \
	chunk_sorting.o external_merge.o input_buffer.o \
	input_buffers_tracker.o input_chunk.o main.o output_buffer.o
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@


clean:
	rm *.o
	rm external_merge
	rm input_file

run: input_file external_merge
	./external_merge input_file

input_file:
	./generator.py input_file 100000 100

all: run

default: all
