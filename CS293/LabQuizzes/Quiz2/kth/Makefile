# Makefile

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11

# Source files
SOURCES = main.cpp kth.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Executable
EXEC = main

# Default target
all: $(EXEC)
	./main

# Link object files to create the executable
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJECTS)

# Compile source files to object files
%.o: %.cpp bst.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

generate: main
	python3 generate-testcases.py tmp 1 1000000
	./main tmp

# Clean up object files and executable
clean:
	rm -f $(OBJECTS) $(EXEC)
	rm -rf *~
	rm -rf output.txt
	rm -rf tmp
