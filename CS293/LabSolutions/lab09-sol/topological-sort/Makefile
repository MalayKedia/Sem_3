COMPILE = g++-11 -std=c++20

all: main.cpp graph.cpp toposort.cpp
	$(COMPILE) main.cpp graph.cpp toposort.cpp -o exec
	./exec < inputs/p1-input.txt > result.txt
	diff -Bw result.txt output/p1-output.txt
	./exec < inputs/p2-input.txt > result.txt
	diff -Bw result.txt output/p2-output.txt

clean:
	rm -rf exec result.txt
