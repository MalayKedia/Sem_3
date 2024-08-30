main: main.cpp
	g++ -std=c++20 -g -Wall -Wextra -Wshadow -Wpedantic $^ -o $@
	./$@

clean:
	rm -rf main
	rm -rf ./*~

.PHONY: main clean
