CXX = g++
CXXFLAGS = -Wall -Wpedantic -Wextra -std=c++14

external_merge: \
	chunk_sorting.o external_merge.o input_buffer.o \
	input_buffers_tracker.o input_chunk.o main.o output_buffer.o
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

run:
	./external_merge input

all: external_merge run

default: external_merge