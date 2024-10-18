CXX = clang++
CXXWARNINGS = -Wall -Wshadow -Wuninitialized -Wtype-limits -Wno-unused-variable
CXXFLAGS = -std=gnu++20 -g -fsanitize=address,undefined $(CXXWARNINGS)
INCLUDEFLAGS = -I/opt/homebrew/opt/llvm/include
LDFLAGS = -lclang -L/opt/homebrew/opt/llvm/lib -rpath /opt/homebrew/opt/llvm/lib

main: main.cpp tokenizer.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDEFLAGS) $(LDFLAGS) $^ -o $@
	rm -rf *.dSYM
	./main

clean:
	rm -rf main *.dSYM

.PHONY: main clean
