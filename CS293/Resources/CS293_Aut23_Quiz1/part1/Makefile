# Makefile for compiling main.cpp

# Compiler
CC = g++
# Compiler flags
CFLAGS = -g -std=c++20 -Wall -Wextra
# Source files
SOURCE = bst.cpp isbst.cpp rotate.cpp main.cpp
# Executable name
EXECUTABLE = bst

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCE) main.cpp
	$(CC) $(CFLAGS) $(SOURCE) -o $(EXECUTABLE)

isbst: $(EXECUTABLE)
	./bst 1

rotate: $(EXECUTABLE)
	./bst 2 > results.txt
	diff testCorrectBST/expectedRotate.txt results.txt

interactive: $(EXECUTABLE)
	./bst 0

clean:
	rm -f $(EXECUTABLE) results.txt
	rm -f *~

.PHONY: clean random english
