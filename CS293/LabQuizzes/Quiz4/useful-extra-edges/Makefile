CPPFILE = useful-extra-edges.cpp
NUM_TESTCASES = 9

TESTCASES = $(foreach tc,$(shell seq 1 $(NUM_TESTCASES)),testcase_$(tc))

.PHONY: all clean

all: $(TESTCASES) clean

testcase_%:
	@echo "Running testcase_$*..."
	g++ -std=c++17 -o testcase_$*.out testcases/testcase_$*.cpp $(CPPFILE) main.cpp
	timeout 10s ./testcase_$*.out > output.txt
	diff -Bw output.txt testcases/output_testcase_$*.txt

clean:
	rm -f testcase_* output.txt 2> /dev/null
	rm -rf *~