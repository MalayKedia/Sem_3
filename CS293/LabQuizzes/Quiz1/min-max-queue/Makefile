# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++20

# Targets
TARGET = main
SOURCES = main.cpp min-max-queue.cpp
HEADERS = min-max-queue.h

all: short long

# Build the executable
$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# Run the executable with an argument
long: $(TARGET)
	tar -xvjf testcases.tar.xy
	./$(TARGET) long > output.txt
	diff output.txt ./testcases/output_long.txt | head -100

short: $(TARGET)
	./$(TARGET) short > output.txt
	diff output.txt ./testcases/output_short.txt

# Clean the build files
clean:
	rm -f $(TARGET)
	rm -rf *~
	rm -rf output.txt

deepclean: clean
	rm -rf testcases
