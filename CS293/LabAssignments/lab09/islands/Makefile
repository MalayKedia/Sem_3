COMPILE = g++-11 -std=c++20

all: ff ic

ff:
	$(COMPILE) run-ff.cpp -o exec
	./exec > result.txt
	diff -Bw output/ff.txt result.txt

ic:
	$(COMPILE) run-ic.cpp -o exec
	./exec > result.txt
	diff -Bw output/ic.txt result.txt

clean:
	rm -rf exec result.txt
