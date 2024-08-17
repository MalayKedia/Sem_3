all: avg-binary

avg-binary: avg-binary.cpp
	g++-11 -std=c++20 -O0 -o binary avg-binary.cpp
	./avg-binary


clean:
	rm -rf run.data
	rm -rf a.out
	rm -rf avg-binary
	rm -rf *~
