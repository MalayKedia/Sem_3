CXX=g++
CXXFLAGS=-std=c++20 -g
CXXWARNINGS=-Wall

all: main runtest1 runtest2 runtest3

main: main.cpp satisfiability.cpp
	$(CXX) $(CXXFLAGS) $(CXXWARNINGS) $^ -o $@
	rm -rf *.o

runtest1: main
	./main one 1.0

runtest2: main
	./main two 1.0

runtest3: main
	./main three 1.0

clean:
	rm -f main *.o
	rm -rf *~

.PHONY: clean
