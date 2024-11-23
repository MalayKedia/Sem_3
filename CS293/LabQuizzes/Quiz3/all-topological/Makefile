# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17

# Targets
TARGET = allsort
SOURCES = main.cpp all-topological-sort.cpp

# Testcase Files
TCDIR = testcases

# Number of Test Cases
NUM_TEST_CASES = 10

all: runtests

# Build the executable
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

runtests: $(TARGET)
	@echo "Running Test Cases"
	@for i in `seq 1 $(NUM_TEST_CASES)`; do \
		echo "\033[0;36m\nTestcase $$i\033[0m"; \
		./$(TARGET) < $(TCDIR)/inputs/$$i.txt > output.txt; \
		cat output.txt | sort > output-sorted.txt; \
		if diff -Bw output-sorted.txt $(TCDIR)/outputs/$$i.txt; then \
			echo "\033[0;32mPASSED\033[0m"; \
		else \
			echo "\033[0;31mFAILED\033[0m"; \
		fi \
	done
	@rm -f output.txt
	@rm -f output-sorted.txt
	@rm -f g.dot

custom: $(TARGET)
	@echo "Running with input file $$file"
	./$(TARGET) < $$file > output.txt
	@echo "Output generated in output.txt"
	@echo "Graph saved in g.dot"

clean:
	rm -rf $(TARGET)
	rm -rf *~
	rm -rf output.txt output-sorted.txt g.dot
