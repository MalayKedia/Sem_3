all: o0 o1 o2 o3

o0: performance.cpp
	g++-11 -std=c++20 -O0 -o performance-O0 performance.cpp
	./performance-O0

o1: performance.cpp
	g++-11 -std=c++20 -O1 -o performance-O1 performance.cpp
	./performance-O1

o2: performance.cpp
	g++-11 -std=c++20 -O2 -o performance-O2 performance.cpp
	./performance-O2

o3: performance.cpp
	g++-11 -std=c++20 -O3 -o performance-O3 performance.cpp
	./performance-O3


clean:
	rm -rf run.data
	rm -rf a.out
	rm -rf binary
	rm -rf performance-O0 performance-O1 performance-O2 performance-O3
	rm -rf a.out
	rm -rf *~
