all: short_1 short_2 long clean

short_1: clash-of-paths.cpp
	g++ -std=c++17 -o short_1 testcases/short_1.cpp clash-of-paths.cpp main.cpp
	timeout 10s ./short_1 > output.txt
	diff -Bw output.txt testcases/expected_output_short_1.txt

short_2: clash-of-paths.cpp
	g++ -std=c++17 -o short_2 testcases/short_2.cpp clash-of-paths.cpp main.cpp
	timeout 10s ./short_2 > output.txt
	diff -Bw output.txt testcases/expected_output_short_2.txt

long: clash-of-paths.cpp
	g++ -std=c++17 -o long testcases/long.cpp clash-of-paths.cpp main.cpp
	timeout 10s ./long > output.txt
	diff -Bw output.txt testcases/expected_output_long.txt

clean:
	rm -f short* long output.txt 2> /dev/null
	rm -rf *~
