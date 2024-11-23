all: test-score test-seq

dummy: test-score test-seq

score: main-score.cpp
	g++ main-score.cpp -o score

test-score: score

	echo "Running test 1..."
	./score < ./test-score/test1>output-score-1
	diff -bw output-score-1 ./test-score/out1.txt && echo "Test 1 passed!" || echo "Test 1 failed!"

	echo "Running test 2..."
	./score < ./test-score/test2>output-score-2
	diff -bw output-score-2 ./test-score/out2.txt && echo "Test 2 passed!" || echo "Test 2 failed!"

	echo "Running test 3..."
	./score < ./test-score/test3>output-score-3
	diff -bw output-score-3 ./test-score/out3.txt && echo "Test 3 passed!" || echo "Test 3 failed!"

	echo "Running test 4..."
	./score < ./test-score/test4>output-score-4
	diff -bw output-score-4 ./test-score/out4.txt && echo "Test 4 passed!" || echo "Test 4 failed!"

	echo "Running test 5..."
	./score < ./test-score/test5>output-score-5
	diff -bw output-score-5 ./test-score/out5.txt && echo "Test 5 passed!" || echo "Test 5 failed!"

seq: main-score.cpp
	g++ main-seq.cpp -o seq

test-seq: seq

	echo "Running test 1..."
	./seq < ./test-seq/test1>output-seq-1
	diff -bw output-seq-1 ./test-seq/out1.txt && echo "Test 1 passed!" || echo "Test 1 failed!"

	echo "Running test 2..."
	./seq < ./test-seq/test2>output-seq-2
	diff -bw output-seq-2 ./test-seq/out2.txt && echo "Test 2 passed!" || echo "Test 2 failed!"

	echo "Running test 3..."
	./seq < ./test-seq/test3>output-seq-3
	diff -bw output-seq-3 ./test-seq/out3.txt && echo "Test 3 passed!" || echo "Test 3 failed!"

	echo "Running test 4..."
	./seq < ./test-seq/test4>output-seq-4
	diff -bw output-seq-4 ./test-seq/out4.txt && echo "Test 4 passed!" || echo "Test 4 failed!"

	echo "Running test 5..."
	./seq < ./test-seq/test5>output-seq-5
	diff -bw output-seq-5 ./test-seq/out5.txt && echo "Test 5 passed!" || echo "Test 5 failed!"

clean:
	rm -f ./seq ./score output*
	rm -f *~
