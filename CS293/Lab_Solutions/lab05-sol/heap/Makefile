# Makefile for compiling main.cpp

# Compiler
CC = g++
# Compiler flags
CFLAGS = -g -std=c++20 -Wall -Wextra
# Source files
SOURCE = main.cpp heap.cpp
# Executable name
EXECUTABLE = heap
EXECUTABLE_RANDOM = heap_random

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(EXECUTABLE)

test: $(EXECUTABLE)
	./heap >> run.txt
	diff run.txt ./tests/output.txt

$(EXECUTABLE_RANDOM): $(SOURCE)
	$(CC) $(CFLAGS) -DRANDOM $(SOURCE) -o $(EXECUTABLE_RANDOM)

random: $(EXECUTABLE_RANDOM)
	./heap_random



clean:
	rm -rf run.txt
	rm -rf heap
	rm -rf heap_random
	rm -rf *~
