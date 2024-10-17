SHELL := /bin/bash

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17

# Targets
TARGET = main
SOURCES = main.cpp
HELP = solution.cpp

# Testcase Files
TCDIR = testcases

all: $(TARGET) run

# Build the executable
$(TARGET): $(SOURCES) $(HELP)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# Run testcases supplied as text files
run: $(TARGET) testcases
	@echo "Running Testcases"
	@for i in {1..15}; do \
		echo -e "\033[0;36m\nTestcase $$i\033[0m"; \
		./$(TARGET) < testcases/inputs/$$i.txt > output.txt; \
		if diff -Bw output.txt testcases/outputs/$$i.txt; then \
			echo -e "\033[0;32mPASSED\033[0m"; \
		else \
			echo -e "\033[0;31mFAILED\033[0m"; \
		fi \
	done
	@rm -f output.txt


# Clean the build files
clean:
	rm -f $(TARGET)
	rm -rf *~
	rm -rf output.txt