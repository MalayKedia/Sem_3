# Makefile
SHELL := /bin/bash

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++17

# Source files
SOURCES = check-tree.cpp main.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Executable
EXEC = check-tree

# Number of Test Cases
NUM_TEST_CASES = 10

# Testcase Files
TCDIR = testcases

# Default target
all: $(EXEC) runtests

# Link object files to create the executable
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJECTS)

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

runtests: $(EXEC)
	@echo -e "Running Test Cases"
	@for i in `seq 1 $(NUM_TEST_CASES)`; do \
		./$(EXEC) < $(TCDIR)/input/$$i.txt > output.txt; \
		echo -e "\033[0;36m\nTestcase $$i\033[0m"; \
		if diff -Bw <(head -n 1 output.txt) <(head -n 1 $(TCDIR)/output/$$i.txt) > /dev/null; then \
			echo -e "\033[0;32mRESULT FLAG CHECK PASSED\033[0m"; \
		else \
			echo -e "\033[0;31mRESULT FLAG CHECK FAILED\033[0m"; \
		fi \
	done
	@rm -f output.txt

# Clean up object files and executable (Unix-like commands)
clean:
	rm -f $(OBJECTS) $(EXEC)
	rm -f *~
