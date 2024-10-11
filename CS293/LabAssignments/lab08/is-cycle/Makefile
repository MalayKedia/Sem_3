# Makefile for compiling main.cpp

# Compiler
CC = g++
# Compiler flags
CFLAGS = -g -std=c++20 -Wall -Wextra
# Source files
SOURCE = main.cpp graph.cpp isCyclePresent.cpp
# Executable name
EXECUTABLE = cycle

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCE) main.cpp
	$(CC) $(CFLAGS) $(SOURCE) -o $(EXECUTABLE)

test: $(EXECUTABLE)
	./cycle < inputs/in1.txt > result.txt
	diff -Bw result.txt outputs/out1.txt
	./cycle < inputs/in2.txt > result.txt
	diff -Bw result.txt outputs/out2.txt
	./cycle < inputs/in3.txt > result.txt
	diff -Bw result.txt outputs/out3.txt
	./cycle < inputs/in4.txt > result.txt
	diff -Bw result.txt outputs/out4.txt
	./cycle < inputs/in5.txt > result.txt
	diff -Bw result.txt outputs/out5.txt
	./cycle < inputs/in6.txt > result.txt
	diff -Bw result.txt outputs/out6.txt

clean:
	rm -f $(EXECUTABLE) result.txt
	rm -f *~

.PHONY: clean
