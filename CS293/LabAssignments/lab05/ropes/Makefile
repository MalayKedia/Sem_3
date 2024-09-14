all: test

exec:
	g++ -std=c++20 main.cpp -o exec

test: exec
	./exec < inputs/input1.txt > out.txt
	diff outputs/output1.txt out.txt
	./exec < inputs/input2.txt > out.txt
	diff outputs/output2.txt out.txt
	./exec < inputs/input3.txt > out.txt
	diff outputs/output3.txt out.txt
	rm out.txt

clean:
	rm -rf exec out.txt
	rm -f *~
