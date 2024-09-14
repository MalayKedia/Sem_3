all:
	g++ -std=c++20 main.cpp -o exec

random: random.cpp
	g++ -std=c++20 random.cpp -o rand
	./rand 10000 > random.txt

test:
	g++ -std=c++20 main.cpp -o exec
	./exec < inputs/input1.txt out.txt
	diff -Bw outputs/output1.txt out.txt
	./exec < inputs/input2.txt out.txt
	diff -Bw outputs/output2.txt out.txt
	./exec < inputs/input3.txt out.txt
	diff -Bw outputs/output3.txt out.txt
	rm out.txt

clean:
	rm -rf exec out.txt rand random.txt
	rm -rf *~
