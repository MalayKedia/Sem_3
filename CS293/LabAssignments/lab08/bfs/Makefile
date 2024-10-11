.PHONY: main part1 part2 clean

COMPILE = g++ -std=c++20 -g -fsanitize=address,undefined

main: main.cpp
	$(COMPILE) main.cpp -o main
	rm -rf main.dSYM

part1: main
	./main < inputs/part1/1.txt > result.txt
	diff -Bw result.txt output/part1/1.txt
	./main < inputs/part1/2.txt > result.txt
	diff -Bw result.txt output/part1/2.txt
	./main < inputs/part1/3.txt > result.txt
	diff -Bw result.txt output/part1/3.txt
	./main < inputs/part1/4.txt > result.txt
	diff -Bw result.txt output/part1/4.txt
	./main < inputs/part1/5.txt > result.txt
	diff -Bw result.txt output/part1/5.txt

part2: main
	./main < inputs/part2/1.txt > result.txt
	diff -Bw result.txt output/part2/1.txt
	./main < inputs/part2/2.txt > result.txt
	diff -Bw result.txt output/part2/2.txt
	./main < inputs/part2/3.txt > result.txt
	diff -Bw result.txt output/part2/3.txt
	./main < inputs/part2/4.txt > result.txt
	diff -Bw result.txt output/part2/4.txt
	./main < inputs/part2/5.txt > result.txt
	diff -Bw result.txt output/part2/5.txt

clean:
	rm -rf main result.txt *~ *.dSYM