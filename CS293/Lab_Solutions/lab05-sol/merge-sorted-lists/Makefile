main: main.cpp
	g++ -std=c++20 -g  $< -o $@
	rm -rf *.dSYM
	./$@

clean:
	rm -rf main
	rm -rf *.dSYM

.PHONY: main clean
