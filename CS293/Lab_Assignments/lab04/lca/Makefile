# Makefile for compiling main.cpp

# Compiler
CC = g++
# Compiler flags
CFLAGS = -g -std=c++20 -Wall -Wextra
# Source files
SOURCE = tree.cpp findlca.cpp main.cpp
# Executable name
EXECUTABLE = tree

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCE) main.cpp
	$(CC) $(CFLAGS) $(SOURCE) -o $(EXECUTABLE)

findlca: $(EXECUTABLE)
	./tree 1 > results.txt
	diff results.txt expectedOutput/outputs.txt

interactive: $(EXECUTABLE)
	./tree 0

clean:
	rm -f $(EXECUTABLE) results.txt
	rm -f *~

.PHONY: clean