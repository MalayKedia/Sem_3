# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17

# Targets
TARGET = program
SOURCES = main.cpp fish.cpp

# Testcase Files
TCDIR = testcases

# Number of Test Cases
NUM_TEST_CASES = 10

all: runtests

# Build the executable
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# Generate test cases using the Python script
generate_testcases:
	@PYTHON=$(shell command -v python || command -v python3 || echo ""); \
	if [ -z "$$PYTHON" ]; then \
		echo "\033[0;31mPython not present\033[0m"; \
		exit 1; \
	fi; \
	if [ -f testcases.tar.gz ]; then \
		echo "\033[0;33mExtracting testcases.tar.gz\033[0m"; \
		tar -xzf testcases.tar.gz; \
	else \
		echo "\033[0;31mtestcases.tar.gz not found!\033[0m"; \
	fi; \
	mkdir -p $(TCDIR)/inputs $(TCDIR)/outputs; \
	$$PYTHON testcases.py

# Run all test cases supplied as JSON files
runtests: $(TARGET) generate_testcases
	@echo "Running Test Cases"
	@for i in `seq 1 $(NUM_TEST_CASES)`; do \
		echo "\033[0;36m\nTestcase $$i\033[0m"; \
		./$(TARGET) < $(TCDIR)/inputs/$$i.txt > output.txt; \
		if diff -Bw output.txt $(TCDIR)/outputs/$$i.txt > /dev/null; then \
			echo "\033[0;32mPASSED\033[0m"; \
		else \
			echo "\033[0;31mFAILED\033[0m"; \
			awk 'NR==FNR{a[NR]=$$0; next} {if (a[FNR] != $$0) { \
				print "\033[0;31mGenerated Output - " $$0 "\033[0m"; \
				print "\033[0;32mExpected output - " a[FNR] "\033[0m"; \
			}}' $(TCDIR)/outputs/$$i.txt output.txt; \
		fi \
	done
	@rm -f output.txt

custom: $(TARGET)
	@echo "Running with input file $$file"
	./$(TARGET) < $$file > output.txt
	@echo "Output generated in output.txt"

# Clean the build files
clean:
	rm -f $(TARGET)
	rm -rf *~
	rm -rf output.txt
