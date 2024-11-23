# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++20

# Targets
TARGET = main
SOURCES = main.cpp swap-pairs.cpp
HEADERS = swap-pairs.h


all: run

# Build the executable
$(TARGET): $(SOURCES) $(HEADERS)
	@#echo $(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

run: $(TARGET)
	./$(TARGET)

# Clean the build files
clean:
	@#echo rm -f $(TARGET)
	rm -f $(TARGET)
	rm -f output.txt
	rm -rf *~
