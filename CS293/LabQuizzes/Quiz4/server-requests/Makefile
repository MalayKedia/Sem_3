CXX=g++
CXXFLAGS=-I ./ -std=c++20 -g 
WARNINGS=-Wall
EXEC=server_requests

all: run

$(EXEC): main.cpp server_requests.cpp testcases/one.cpp testcases/two.cpp testcases/three.cpp
	$(CXX) $(CXXFLAGS) $(WARNINGS) $^ -o $@

run: $(EXEC)
	./$(EXEC)

clean:
	rm -rf $(EXEC) *.o
	rm -rf *~
