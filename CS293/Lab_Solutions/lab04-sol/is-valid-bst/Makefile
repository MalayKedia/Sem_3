main: main.cpp
	g++ -std=c++20 -fsanitize=address,undefined -g -Wall -Wextra -Wshadow -Wpedantic -Werror $^ -o $@
	rm -rf *.dSYM
	./$@

clean:
	rm -rf main *.dSYM
	rm -rf *~

.PHONY: main clean
