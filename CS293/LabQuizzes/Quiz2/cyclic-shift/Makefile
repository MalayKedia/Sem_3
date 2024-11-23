# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17

# Targets
TARGET = main
SOURCES = cyclic.cpp main.cpp

# Testcase Files
TCZIP = testcases.tar.gz
TCDIR = testcases

# Number of TCs
SHORT = 8
LONG = 12

all: short

# Build the executable
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# Extracts testcases
testcases: $(TCZIP)
	@if [ ! -d "$(TCDIR)" ]; then \
		echo "Extracting testcases..."; \
		tar -xvf $(TCZIP); \
	else \
		echo "Testcases already extracted."; \
	fi

# Run short testcases supplied as text files
short: $(TARGET) testcases
	@echo "Running Short Testcases"
	@for i in `seq $(shell echo 1 | bc) $(shell echo $(SHORT) | bc)`; do \
		echo "\033[0;36m\nTestcase $$i\033[0m"; \
		./$(TARGET) < testcases/inputs/$$i.txt > output.txt; \
		if diff -Bw output.txt testcases/outputs/$$i.txt; then \
			echo "\033[0;32mPASSED\033[0m"; \
		else \
			echo "\033[0;31mFAILED\033[0m"; \
		fi \
	done
	@rm -f output.txt

# Run long testcases (requires python)
long: $(TARGET) testcases
	@echo "Running Long Testcases"
	@PYTHON=$(shell command -v python || command -v python3 || echo ""); \
	if [ -z "$$PYTHON" ]; then \
		echo "\033[0;31mPython not present\033[0m"; \
		exit 1; \
	fi; \
	for i in `seq $(shell echo $(SHORT)+1 | bc) $(shell echo $(SHORT)+$(LONG) | bc)`; do \
		echo "\033[0;36m\nTestcase $$i\033[0m"; \
		if [ $$i -lt 14 ]; then \
			./$(TARGET) < testcases/inputs/$$i.txt > output.txt; \
		else \
			echo $$i | $$PYTHON testcases/inputs/input.py | ./$(TARGET) > output.txt; \
		fi; \
		if diff -Bw output.txt testcases/outputs/$$i.txt; then \
			echo "\033[0;32mPASSED\033[0m"; \
		else \
			echo "\033[0;31mFAILED\033[0m"; \
		fi \
	done
	@rm -f output.txt


# Clean the build files
clean:
	rm -f $(TARGET)
	rm -rf *~
	rm -rf output.txt
	rm -rf $(TCDIR)
