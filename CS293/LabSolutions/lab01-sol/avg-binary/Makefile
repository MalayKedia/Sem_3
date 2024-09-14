all: avg-binary

avg-binary: avg-binary.cpp
	g++-11 -std=c++20 -O0 -o avg-binary avg-binary.cpp
	./avg-binary

clean:
	rm -rf avg-binary
	rm -rf *~
