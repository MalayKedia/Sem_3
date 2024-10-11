main: main.cpp encode_tree.cpp decode_tree.cpp
	g++ -std=c++20 -g -fsanitize=address,undefined -Wall -Wextra -Wshadow -Wpedantic -Wno-writable-strings -Wno-write-strings $^ -o $@
	rm -rf *.dSYM *.o
	./$@

clean:
	rm -rf main *.o *.dSYM

.PHONY: main clean