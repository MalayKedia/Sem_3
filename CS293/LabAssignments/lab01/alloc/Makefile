all: alloc

alloc:
	g++-11 -std=c++20 alloc.cpp
	./a.out > run.data
	gnuplot -persist plot.p

clean:
	rm -rf run.data
	rm -rf a.out
	rm -rf binary
	rm -rf performance-O0 performance-O1 performance-O2 performance-O3
	rm -rf a.out
	rm -rf *~
