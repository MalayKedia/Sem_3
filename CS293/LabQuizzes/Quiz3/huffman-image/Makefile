# Makefile
SHELL := /bin/bash

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11

# Source files
SOURCES = huffman.cpp main.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Executable
EXEC = main

# Number of Test Cases
NUM_TEST_CASES = 9

# Testcase Files
TCDIR = testcases

# Default target
all: generate runtests

# Link object files to create the executable
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJECTS)

# Compile source files to object files
%.o: %.cpp huffman.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

generate: $(EXEC)
	python3 testcases.py 1
	./$(EXEC)
	python3 testcases.py 2

runtests: $(EXEC) generate
	@echo -e "Running Test Cases"
	@for i in `seq 0 $(NUM_TEST_CASES)`; do \
		echo -e "\033[0;36m\nTestcase $$i\033[0m"; \
		if diff -Bw <(head -n 1 $(TCDIR)/compressed_output/testcase_compressed_img$$i.txt) <(head -n 1 $(TCDIR)/expected_output/testcase_img$$i.txt); then \
			echo -e "\033[0;32mPASSED\033[0m"; \
		else \
			echo -e "\033[0;31mFAILED\033[0m"; \
		fi \
	done
	@rm -f output.txt

# Clean up object files and executable (Unix-like commands)
clean:
	rm -f $(OBJECTS) $(EXEC)
	rm -f *~
