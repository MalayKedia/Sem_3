CXX=g++
CXXFLAGS=-std=c++20 -g -fsanitize=address,undefined
CXXWARNINGS=-Wall
#-Wshadow -Wuninitialized -Wtype-limits -Wno-unused-variable -Wpedantic

main: main.cpp satisfiability.cpp
	$(CXX) $(CXXFLAGS) $(CXXWARNINGS) $^ -o $@

runtest1: main
	./main one 1.0

runtest2: main
	./main two 1.0

runtest3: main
	./main three 1.0

clean:
	rm -f main *.o *.dSYM

.PHONY: clean
