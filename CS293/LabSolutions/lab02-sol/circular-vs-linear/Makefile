
both: linear circular
	gnuplot -persist plot.p

linear: queue.h linearQueue.cpp test.cpp
	g++ -g -D LINEAR -o linear test.cpp
	./linear > linear.data


circular: queue.h circularQueue.cpp test.cpp
	g++ -g -D CIRCULAR -o circular test.cpp
	./circular > circular.data


clean:
	rm -rf linear circular linear.data circular.data
	rm -rf *~
