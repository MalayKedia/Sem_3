# Compiler and flags
CC = g++ -std=c++17
CFLAGS = -Wall -Werror -Wno-return-type -g

# Target executable
TARGET = main

# Source files
SRCS = main.cpp leftistHeap.cpp heap.cpp

# Testcase FIles
TCZIP = testcases.tar.gz
TCDIR = testcases

all: $(TARGET) testcases check

testcases: $(TCZIP)
	@if [ ! -d $(TCDIR) ]; then \
		echo "Extracting testcases..."; \
		tar -xzf $(TCZIP); \
	else \
		echo "Testcases already extracted."; \
	fi

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

check: $(TARGET) testcases
	./$(TARGET) 0

interactive: $(TARGET)
	./$(TARGET) 1

clean:
	rm -f $(TARGET)
	rm -rf $(TCDIR)
	rm -rf *~
