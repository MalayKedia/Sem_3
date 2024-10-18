CXX = clang++
CXXWARNINGS = -Wall -Wshadow -Wuninitialized -Wtype-limits -Wno-unused-variable
CXXFLAGS = -std=gnu++20 -g -fsanitize=address,undefined $(CXXWARNINGS)
INCLUDEFLAGS = -I/usr/lib/llvm-18/include
LDFLAGS = -lclang -L/usr/lib/llvm-18/lib -rpath /usr/lib/llvm-18/lib

main: main.cpp plagiarism_checker.cpp tokenizer.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDEFLAGS) $(LDFLAGS) $^ -o $@
	rm -rf *.dSYM
	./main > output.txt
	diff -Bw testcase/expected.txt output.txt

clean:
	rm -rf main output.txt *.dSYM

.PHONY: main clean
