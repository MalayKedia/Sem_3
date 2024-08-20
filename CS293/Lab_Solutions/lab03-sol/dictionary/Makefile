# Makefile for compiling dictionaryTest.cpp

# Compiler
CC = g++
# Compiler flags
CFLAGS = -std=c++20 -Wall -Wextra
# Source files
SOURCE = dictionaryTest.cpp
# Executable name
EXECUTABLE = exec

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCE) dictionary.cpp
	$(CC) $(CFLAGS) $(SOURCE) -o $(EXECUTABLE)

runtests: $(EXECUTABLE)
	./exec 0 < inputs/input1.txt > output.txt
	diff ./inputs/output1.txt output.txt

random: $(EXECUTABLE)
	python3 sampler.py
	./exec 1 > results.txt
	python3 plot.py

english: $(EXECUTABLE)
	./exec 2 > results.txt
	python3 plot.py

clean:
	rm -f $(EXECUTABLE) sample.txt results.txt Hash.png output.txt

.PHONY: clean random english
