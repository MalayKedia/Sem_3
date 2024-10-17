main: main.cpp optimal_paths.cpp
	g++ -std=c++20 -g -fsanitize=address,undefined $^ -o $@
	rm -rf *.dSYM
	./main

clean:
	rm -rf main

.PHONY: main clean
