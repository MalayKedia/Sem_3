# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -std=c++17

# Directories
INPUT_DIR := inputs
OUTPUT_DIR := output
EXPECTED_DIR := expected_outputs

# Executable name
EXECUTABLE := my_program

# Find all input files
INPUT_FILES := $(wildcard $(INPUT_DIR)/*.txt)

# Define output files based on input files
OUTPUT_FILES := $(patsubst $(INPUT_DIR)/%.txt, $(OUTPUT_DIR)/%.txt, $(INPUT_FILES))

# Default target: Compile and run all steps
all: $(EXECUTABLE) $(OUTPUT_FILES) diff

# Compile main.cpp into executable
$(EXECUTABLE): main.cpp num-min-paths.cpp
	$(CXX) $(CXXFLAGS) -o $@ main.cpp num-min-paths.cpp

# Rule to create the output directory if it doesn't exist
$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

# Rule to run the program on each input file and store the result in the output directory
$(OUTPUT_DIR)/%.txt: $(INPUT_DIR)/%.txt | $(EXECUTABLE) $(OUTPUT_DIR)
	./$(EXECUTABLE) < $< > $@

# Rule to compare output files with expected output files
diff: $(OUTPUT_FILES)
	@echo "Comparing output with expected output..."
	@for file in $(OUTPUT_FILES); do \
		expected_file=$(EXPECTED_DIR)/$$(basename $$file); \
		if [ -f $$expected_file ]; then \
			diff -bw -q $$file $$expected_file || echo "Difference found in $$file"; \
		else \
			echo "Expected output for $$file not found!"; \
		fi; \
	done
	@echo "Comparison complete."

# Clean up output files and the executable
clean:
	rm -rf $(OUTPUT_DIR) $(EXECUTABLE)
	rm -rf *~
