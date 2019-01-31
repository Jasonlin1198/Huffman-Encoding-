# A makefile for CSE 100 PA2

# === Directories ===
SRC=src
BUILD=build
OBJ=$(BUILD)/obj

# === Compiler options ===
# use g++ for everything
CC=g++

# MMD: automatically resolve included files
# g: include debugging symbols in the generated object file
# Wall: enable all warnings
# std: language standard to compile for
CXXFLAGS=-MMD -g -Wall -std=c++11
LDFLAGS=-g

# === Build targets ===
default: compress uncompress test benchmark

BENCHMARK_HPP=$(wildcard $(SRC)/benchmark/*.hpp)
BENCHMARK_CPP=$(wildcard $(SRC)/benchmark/*.cpp)
BENCHMARK_OBJ=$(patsubst $(SRC)/benchmark/%.cpp,$(OBJ)/benchmark/%.o,$(BENCHMARK_CPP))
benchmark: $(BUILD)/benchmark
$(BUILD)/benchmark: $(BENCHMARK_OBJ)
	$(CC) $(LDFLAGS) $+ -o $@
$(OBJ)/benchmark/%.o: $(SRC)/benchmark/%.cpp $(BENCHMARK_HPP)
	@ mkdir -p $(OBJ)/benchmark
	$(CC) $(CXXFLAGS) -c $< -o $@

$(OBJ)/%.o: $(SRC)/%.cpp $(SRC)/*.hpp
	@ mkdir -p $(OBJ)
	$(CC) $(CXXFLAGS) -c $< -o $@

SHARED_OBJ=$(OBJ)/HCNode.o $(OBJ)/HCTree.o $(OBJ)/BitInputStream.o $(OBJ)/BitOutputStream.o

$(BUILD)/%: $(OBJ)/%.o $(SHARED_OBJ)
	$(CC) $(LDFLAGS) $< $(SHARED_OBJ) -o $@

clean:
	rm -rf $(BUILD)

compress: $(BUILD)/compress
uncompress: $(BUILD)/uncompress
codec: compress uncompress

test: test_checkpoint test_final
test_checkpoint: $(BUILD)/test_checkpoint
test_final: $(BUILD)/test_final

zip: $(SRC)/*
	@ rm -f submission.zip
	zip -r submission.zip $(SRC) --exclude '*catch.hpp' '*test_*' '*/benchmark/*'

.PHONY: default clean compress uncompress test test_checkpoint test_final codec zip benchmark
