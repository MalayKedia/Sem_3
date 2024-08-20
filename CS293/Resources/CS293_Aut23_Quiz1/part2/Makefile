# Makefile for compiling main.cpp

# Compiler
CC = g++
# Compiler flags
CFLAGS = -g -std=c++20 -Wall -Wextra
# Source files
SOURCE = long.cpp
# Executable name
EXECUTABLE = long

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(EXECUTABLE)

longtest: $(EXECUTABLE)
	./long "()"     > ./results.txt
	./long "(()"   >> ./results.txt
	./long ")()"   >> ./results.txt
	./long "()()"  >> ./results.txt
	./long "()())" >> ./results.txt
	diff expected.txt results.txt


clean:
	rm -f $(EXECUTABLE) results.txt
	rm -f *~

.PHONY: clean lontest
