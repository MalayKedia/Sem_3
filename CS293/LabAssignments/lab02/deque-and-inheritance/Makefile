deque: deque-inheritance.cpp deque-test.cpp
	g++ -std=c++20 -o deque deque-test.cpp

runtests: deque
	./deque < ./inputs/input-1.txt > output.txt
	diff ./outputs/output-1.txt output.txt
	./deque < ./inputs/input-2.txt > output.txt
	diff ./outputs/output-2.txt output.txt
	./deque < ./inputs/input-3.txt > output.txt
	diff ./outputs/output-3.txt output.txt
	./deque < ./inputs/input-4.txt > output.txt
	diff ./outputs/output-4.txt output.txt

clean:
	rm -rf ./deque output.txt
	rm -rf *~
