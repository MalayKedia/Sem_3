# Compiler
CC = g++
# Compiler flags
CFLAGS = -std=c++20 -Wall -Wextra -Wno-unused-parameter -Wno-unused-private-field -Werror
# Source files
SOURCE = limitedDictTest.cpp
# Executable name
EXECUTABLE = exec

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCE) dictionary.cpp limitedDictionary.cpp
	$(CC) $(CFLAGS) $(SOURCE) -o $(EXECUTABLE)

runfifo: $(EXECUTABLE)
	echo "fifo" | ./$(EXECUTABLE) > temp.txt 2>&1
	diff temp.txt expected_outputs/small_fifo.txt
	rm temp.txt

runlru: $(EXECUTABLE)
	echo "lru" | ./$(EXECUTABLE) > temp.txt 2>&1
	diff temp.txt expected_outputs/small_lru.txt
	rm temp.txt

clean:
	rm -f $(EXECUTABLE)

.PHONY: clean
